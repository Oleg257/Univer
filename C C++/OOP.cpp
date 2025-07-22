#include <iostream>
#include <string>


class Investor {
private:
    std::string lastName;
    std::string district;
    double depositAmount;

public:
    Investor(const std::string& lastName, const std::string& district, double depositAmount)
        : lastName(lastName), district(district), depositAmount(depositAmount) {}

    virtual void displayInfo() const = 0;
    
    std::string getLastName() const {
        return lastName;
    }

    std::string getDistrict() const {
        return district;
    }

    double getDepositAmount() const {
        return depositAmount;
    }

    virtual ~Investor() {}
};


class Employee : public Investor {
private:
    std::string position;
    static int employeeCount; 
public:
    Employee(const std::string& lastName, const std::string& district, double depositAmount, const std::string& position)
        : Investor(lastName, district, depositAmount), position(position) {
        employeeCount++;
    }

    void displayInfo() const override {
        std::cout << "Employee: " << getLastName() << ", District: " << getDistrict()
                  << ", Position: " << position << ", Deposit: " << getDepositAmount() << std::endl;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }
    
    ~Employee() {
        employeeCount--;
    }
};

int Employee::employeeCount = 0;

class Worker : public Investor {
private:
    std::string profession;
    static int workerCount;  
public:
    Worker(const std::string& lastName, const std::string& district, double depositAmount, const std::string& profession)
        : Investor(lastName, district, depositAmount), profession(profession) {
        workerCount++;
    }

    void displayInfo() const override {
        std::cout << "Worker: " << getLastName() << ", District: " << getDistrict()
                  << ", Profession: " << profession << ", Deposit: " << getDepositAmount() << std::endl;
    }

    static int getWorkerCount() {
        return workerCount;
    }
    
    ~Worker() {
        workerCount--;
    }
};

int Worker::workerCount = 0;

class Entrepreneur : public Investor {
private:
    std::string businessType;
    static int entrepreneurCount;
public:
    Entrepreneur(const std::string& lastName, const std::string& district, double depositAmount, const std::string& businessType)
        : Investor(lastName, district, depositAmount), businessType(businessType) {
        entrepreneurCount++;
    }

    void displayInfo() const override {
        std::cout << "Entrepreneur: " << getLastName() << ", District: " << getDistrict()
                  << ", Business Type: " << businessType << ", Deposit: " << getDepositAmount() << std::endl;
    }

    static int getEntrepreneurCount() {
        return entrepreneurCount;
    }
    
    ~Entrepreneur() {
        entrepreneurCount--;
    }
};

int Entrepreneur::entrepreneurCount = 0;

int main() {
    Investor* investors[] = {
        new Employee("Smith", "Central", 5000.0, "Manager"),
        new Employee("Bob", "North", 3000.0, "Supervisor"),
        new Worker("Taylor", "South", 4000.0, "Mechanic"),
        new Worker("Clark", "East", 3500.0, "Technician"),
        new Entrepreneur("Brown", "West", 10000.0, "Retail"),
        new Entrepreneur("White", "Central", 12000.0, "Technology"),
    };

    for (const auto& investor : investors) {
        investor->displayInfo();
    }

    std::cout << "\nEmployee Count: " << Employee::getEmployeeCount() << std::endl;
    std::cout << "Worker Count: " << Worker::getWorkerCount() << std::endl;
    std::cout << "Entrepreneur Count: " << Entrepreneur::getEntrepreneurCount() << std::endl;

    for (const auto& investor : investors) {
        delete investor;
    }

    return 0;
}