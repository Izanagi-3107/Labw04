/*
 * Mã sinh viên: 202418984
 * Họ tên: Ngô Ngọc Thái
 * Bài thực hành: Lab03-04 - Nhóm dự án và nhân sự
 */
#include "SalesEmployee.h"

#include <iostream>
#include <stdexcept>

SalesEmployee::SalesEmployee(const std::string& employeeId,
                             const std::string& fullName, double baseSalary)
    : SalesEmployee(employeeId, fullName, "Unassigned", baseSalary, 0, 0) {
}

SalesEmployee::SalesEmployee(const std::string& employeeId,
                             const std::string& fullName,
                             const std::string& department, double baseSalary,
                             double salesRevenue, double commissionRate)
    : Employee(employeeId, fullName, department), baseSalary(baseSalary),
      salesRevenue(salesRevenue), commissionRate(commissionRate) {
    validateNonNegative(baseSalary, "Base salary");
    validateNonNegative(salesRevenue, "Sales revenue");
    validateNonNegative(commissionRate, "Commission rate");
    if (commissionRate > 0.3) {
        throw std::invalid_argument("Commission rate must not exceed 0.3.");
    }
}

double SalesEmployee::getBaseSalary() const {
    return baseSalary;
}

double SalesEmployee::getSalesRevenue() const {
    return salesRevenue;
}

double SalesEmployee::getCommissionRate() const {
    return commissionRate;
}

void SalesEmployee::setSalesRevenue(double salesRevenue) {
    validateNonNegative(salesRevenue, "Sales revenue");
    this->salesRevenue = salesRevenue;
}

double SalesEmployee::calculateGrossPay() const {
    return baseSalary + salesRevenue * commissionRate + getMonthlyBonus();
}

std::string SalesEmployee::getEmployeeType() const {
    return "SalesEmployee";
}

void SalesEmployee::displayPayrollInfo() const {
    displayCommonInfo();
    std::cout << "Luong co ban: " << baseSalary << '\n';
    std::cout << "Doanh so: " << salesRevenue << '\n';
    std::cout << "Ty le hoa hong: " << commissionRate * 100 << "%\n";
    std::cout << "Tien hoa hong: " << salesRevenue * commissionRate << '\n';
    std::cout << "Thuong: " << getMonthlyBonus() << '\n';
    std::cout << "Thu nhap: " << calculateGrossPay() << '\n';
}
