#ifndef board_h
#define board_h

#define SIZE 4

extern int board[SIZE][SIZE];
extern int empty_row, empty_col;

void initialize_board();
void mixing_board();
void print_board();
int is_solved();
void make_move(char move);

#endif
