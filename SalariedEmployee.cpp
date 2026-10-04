/*
 * Mã sinh viên: 202418984
 * Họ tên: Ngô Ngọc Thái
 * Bài thực hành: Lab03-04 - Nhóm dự án và nhân sự
 */
#include "SalariedEmployee.h"

#include <iostream>

SalariedEmployee::SalariedEmployee(const std::string& employeeId,
                                   const std::string& fullName, double monthlySalary)
    : SalariedEmployee(employeeId, fullName, "Unassigned", monthlySalary, 0) {
}

SalariedEmployee::SalariedEmployee(const std::string& employeeId,
                                   const std::string& fullName,
                                   const std::string& department, double monthlySalary,
                                   double responsibilityAllowance)
    : Employee(employeeId, fullName, department), monthlySalary(monthlySalary),
      responsibilityAllowance(responsibilityAllowance) {
    validateNonNegative(monthlySalary, "Monthly salary");
    validateNonNegative(responsibilityAllowance, "Responsibility allowance");
}

double SalariedEmployee::getMonthlySalary() const {
    return monthlySalary;
}

double SalariedEmployee::getResponsibilityAllowance() const {
    return responsibilityAllowance;
}

double SalariedEmployee::calculateGrossPay() const {
    return monthlySalary + responsibilityAllowance + getMonthlyBonus();
}

std::string SalariedEmployee::getEmployeeType() const {
    return "SalariedEmployee";
}

void SalariedEmployee::displayPayrollInfo() const {
    displayCommonInfo();
    std::cout << "Luong thang: " << monthlySalary << '\n';
    std::cout << "Phu cap trach nhiem: " << responsibilityAllowance << '\n';
    std::cout << "Thuong: " << getMonthlyBonus() << '\n';
    std::cout << "Thu nhap: " << calculateGrossPay() << '\n';
}
