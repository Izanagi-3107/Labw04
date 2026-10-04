#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    const std::string employeeId;
    std::string fullName;
    std::string department;
    double monthlyBonus;

protected:
    static void validateText(const std::string& value, const std::string& field);
    static void validateNonNegative(double value, const std::string& field);
    void displayCommonInfo() const;

public:
    Employee(const std::string& employeeId, const std::string& fullName);
    Employee(const std::string& employeeId, const std::string& fullName,
             const std::string& department);
    virtual ~Employee() = default;

    const std::string& getEmployeeId() const;
    const std::string& getFullName() const;
    const std::string& getDepartment() const;
    double getMonthlyBonus() const;

    void addBonus(double amount);
    void addBonus(double amount, const std::string& reason);
    void addBonus(double rate, double referenceAmount, const std::string& reason);
    void resetMonthlyBonus();

    virtual double calculateGrossPay() const = 0;
    virtual std::string getEmployeeType() const = 0;
    virtual void displayPayrollInfo() const = 0;
};

#endif
