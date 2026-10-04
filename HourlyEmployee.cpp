/*
 * Mã sinh viên: 202418984
 * Họ tên: Ngô Ngọc Thái
 * Bài thực hành: Lab03-04 - Nhóm dự án và nhân sự
 */
#include "HourlyEmployee.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

HourlyEmployee::HourlyEmployee(const std::string& employeeId,
                               const std::string& fullName, double hourlyRate)
    : HourlyEmployee(employeeId, fullName, "Unassigned", hourlyRate, 0) {
}

HourlyEmployee::HourlyEmployee(const std::string& employeeId,
                               const std::string& fullName,
                               const std::string& department, double hourlyRate,
                               double workedHours)
    : Employee(employeeId, fullName, department), hourlyRate(hourlyRate),
      workedHours(workedHours) {
    validateNonNegative(hourlyRate, "Hourly rate");
    validateNonNegative(workedHours, "Worked hours");
    if (workedHours > 250) {
        throw std::invalid_argument("Worked hours must not exceed 250.");
    }
}

double HourlyEmployee::getHourlyRate() const {
    return hourlyRate;
}

double HourlyEmployee::getWorkedHours() const {
    return workedHours;
}

double HourlyEmployee::getRegularHours() const {
    return std::min(workedHours, 160.0);
}

double HourlyEmployee::getOvertimeHours() const {
    return std::max(workedHours - 160.0, 0.0);
}

double HourlyEmployee::calculateGrossPay() const {
    return getRegularHours() * hourlyRate
           + getOvertimeHours() * hourlyRate * 1.5
           + getMonthlyBonus();
}

std::string HourlyEmployee::getEmployeeType() const {
    return "HourlyEmployee";
}

void HourlyEmployee::displayPayrollInfo() const {
    displayCommonInfo();
    std::cout << "Don gia gio: " << hourlyRate << '\n';
    std::cout << "So gio lam: " << workedHours << '\n';
    std::cout << "Gio thuong: " << getRegularHours() << '\n';
    std::cout << "Gio lam them: " << getOvertimeHours() << '\n';
    std::cout << "Tien gio thuong: " << getRegularHours() * hourlyRate << '\n';
    std::cout << "Tien lam them: " << getOvertimeHours() * hourlyRate * 1.5 << '\n';
    std::cout << "Thuong: " << getMonthlyBonus() << '\n';
    std::cout << "Thu nhap: " << calculateGrossPay() << '\n';
}
