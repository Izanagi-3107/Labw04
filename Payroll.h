#ifndef PAYROLL_H
#define PAYROLL_H

#include "Employee.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Payroll {
private:
    std::string period;
    std::vector<std::unique_ptr<Employee>> employees;

public:
    explicit Payroll(const std::string& period);

    const std::string& getPeriod() const;
    std::size_t getEmployeeCount() const;
    bool addEmployee(std::unique_ptr<Employee> employee);
    Employee* findEmployee(const std::string& employeeId);
    const Employee* findEmployee(const std::string& employeeId) const;
    double calculateTotalPayroll() const;
    double calculatePayrollByDepartment(const std::string& department) const;
    const Employee* findHighestPaidEmployee() const;
    void displayPayroll() const;
};

#endif
