/*
 * Mã sinh viên: 202418984
 * Họ tên: Ngô Ngọc Thái
 * Bài thực hành: Lab03-04 - Nhóm dự án và nhân sự
 */
#ifndef SALARIED_EMPLOYEE_H
#define SALARIED_EMPLOYEE_H

#include "Employee.h"

class SalariedEmployee : public Employee {
private:
    double monthlySalary;
    double responsibilityAllowance;

public:
    SalariedEmployee(const std::string& employeeId, const std::string& fullName,
                     double monthlySalary);
    SalariedEmployee(const std::string& employeeId, const std::string& fullName,
                     const std::string& department, double monthlySalary,
                     double responsibilityAllowance);

    double getMonthlySalary() const;
    double getResponsibilityAllowance() const;
    double calculateGrossPay() const override;
    std::string getEmployeeType() const override;
    void displayPayrollInfo() const override;
};

#endif
