#ifndef SALES_EMPLOYEE_H
#define SALES_EMPLOYEE_H

#include "Employee.h"

class SalesEmployee : public Employee {
private:
    double baseSalary;
    double salesRevenue;
    double commissionRate;

public:
    SalesEmployee(const std::string& employeeId, const std::string& fullName,
                  double baseSalary);
    SalesEmployee(const std::string& employeeId, const std::string& fullName,
                  const std::string& department, double baseSalary,
                  double salesRevenue, double commissionRate);

    double getBaseSalary() const;
    double getSalesRevenue() const;
    double getCommissionRate() const;
    void setSalesRevenue(double salesRevenue);
    double calculateGrossPay() const override;
    std::string getEmployeeType() const override;
    void displayPayrollInfo() const override;
};

#endif
