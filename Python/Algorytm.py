import sys

class Optimizer:
    def __init__(self):
        self.n = 0
        self.m = 0
        self.is_maximize = True
        self.matrix = []
        self.constants = []
        self.objective = []
        self.basis = []
        self.grid = []
        self.step = 0

    def read_data(self, filename):
        with open(filename, 'r') as file:
            lines = [line.strip() for line in file if line.strip()]
        if not lines:
            raise ValueError("Empty file")

        parts = lines[0].split()
        self.is_maximize = parts[0] == 'max'
        self.objective = [float(x) for x in parts[1:]]
        self.n = len(self.objective)
        if not self.is_maximize:
            self.objective = [-x for x in self.objective]

        constraints = []
        for line in lines[1:]:
            parts = line.split()
            row = [float(x) for x in parts[:self.n]]
            sign = parts[self.n]
            value = float(parts[self.n + 1])
            if sign == '>=':
                row = [-x for x in row]
                value = -value
                sign = '<='
            if sign not in ('<=', '='):
                raise ValueError("Invalid constraint type")
            constraints.append((row, value, sign))

        self.m = len(constraints)

        slack_count = sum(1 for (_, _, s) in constraints if s == '<=')
        self.matrix, self.constants, self.basis = [], [], []
        slack_index = 0
        for row, value, sign in constraints:
            slack = [0.0] * slack_count
            if sign == '<=':
                slack[slack_index] = 1.0
                self.basis.append(self.n + slack_index)
                slack_index += 1
            self.matrix.append(row + slack)
            self.constants.append(value)

        self.objective = self.objective + [0.0] * slack_count

        cols = self.n + slack_count
        self.grid = [[0.0] * (cols + 1) for _ in range(self.m + 1)]

        for i in range(self.m):
            for j in range(cols):
                self.grid[i][j] = self.matrix[i][j]
            self.grid[i][-1] = self.constants[i]

        for j in range(cols):
            self.grid[self.m][j] = -self.objective[j]
        self.grid[self.m][-1] = 0.0

        self.display_grid()

    def display_grid(self):
        rows = len(self.grid) - 1
        cols = len(self.grid[0]) - 1
        header = [f"x{j+1}" for j in range(cols)] + ["RHS"]
        print(f"Iter {self.step}")
        print("Base   ", "  ".join(f"{h:>6}" for h in header))
        for i in range(rows + 1):
            var = f"x{self.basis[i]+1}" if i < rows else "  z  "
            row = [f"{self.grid[i][j]:>6.2f}" for j in range(cols)] + [f"{self.grid[i][-1]:>6.2f}"]
            print(f"{var:>5}  ", "  ".join(row))
        print()

    def extract_solution(self):
        solution = [0.0] * (len(self.grid[0]) - 1)
        for i in range(self.m):
            if i < len(self.basis):
                solution[self.basis[i]] = self.grid[i][-1]
        for i in range(self.n):
            print(f"x{i+1} = {solution[i]:.2f}")
        
        z_value = self.grid[self.m][-1]
        if not self.is_maximize:
            z_value = -z_value
        print(f"z = {z_value:.2f}")

    def pivot_operation(self, r, c):
        pivot = self.grid[r][c]
        for j in range(len(self.grid[0])):
            self.grid[r][j] /= pivot
        for i in range(len(self.grid)):
            if i != r:
                factor = self.grid[i][c]
                for j in range(len(self.grid[0])):
                    self.grid[i][j] -= factor * self.grid[r][j]
        self.basis[r] = c

    def optimize(self):
        if any(self.grid[self.m][j] < 0 for j in range(len(self.grid[0]) - 1)):
            print("Ошибка: строка z содержит отрицательные коэффициенты.")
            sys.exit(1)

        while True:
            r = min(
                (i for i in range(self.m) if self.grid[i][-1] < 0),
                default=-1,
                key=lambda i: self.grid[i][-1],
            )
            if r == -1:
                break

            candidates = [
                (self.grid[self.m][j] / self.grid[r][j], j)
                for j in range(len(self.grid[0]) - 1)
                if self.grid[r][j] < 0
            ]
            if not candidates:
                print("No solution")
                return

            c = max(candidates)[1]
            self.step += 1
            self.pivot_operation(r, c)
            print(f"Iteration {self.step} (pivot r={r+1}, c={c+1}):")
            self.display_grid()

        print("Optimal solution:")
        self.extract_solution()

def main():
    filename = 'input.txt'
    optimizer = Optimizer()
    optimizer.read_data(filename)
    optimizer.optimize()

if __name__ == '__main__':
    main()
