#include "Employee.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Employee::Employee(const std::string& employeeId, const std::string& fullName)
    : Employee(employeeId, fullName, "Unassigned") {
}

Employee::Employee(const std::string& employeeId, const std::string& fullName,
                   const std::string& department)
    : employeeId(employeeId), fullName(fullName), department(department),
      monthlyBonus(0) {
    validateText(employeeId, "Employee ID");
    validateText(fullName, "Full name");
    validateText(department, "Department");
}

void Employee::validateText(const std::string& value, const std::string& field) {
    if (value.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument(field + " must not be empty.");
    }
}

void Employee::validateNonNegative(double value, const std::string& field) {
    if (!std::isfinite(value) || value < 0) {
        throw std::invalid_argument(field + " must be finite and non-negative.");
    }
}

const std::string& Employee::getEmployeeId() const {
    return employeeId;
}

const std::string& Employee::getFullName() const {
    return fullName;
}

const std::string& Employee::getDepartment() const {
    return department;
}

double Employee::getMonthlyBonus() const {
    return monthlyBonus;
}

void Employee::addBonus(double amount) {
    if (!std::isfinite(amount) || amount <= 0) {
        throw std::invalid_argument("Bonus amount must be finite and positive.");
    }

    double newBonus = monthlyBonus + amount;
    if (!std::isfinite(newBonus)) {
        throw std::overflow_error("Monthly bonus is too large.");
    }

    monthlyBonus = newBonus;
}

void Employee::addBonus(double amount, const std::string& reason) {
    validateText(reason, "Bonus reason");
    addBonus(amount);
}

void Employee::addBonus(double rate, double referenceAmount,
                        const std::string& reason) {
    if (!std::isfinite(rate) || rate <= 0 || rate > 0.5) {
        throw std::invalid_argument("Bonus rate must be in (0, 0.5].");
    }
    if (!std::isfinite(referenceAmount) || referenceAmount <= 0) {
        throw std::invalid_argument("Reference amount must be finite and positive.");
    }

    addBonus(rate * referenceAmount, reason);
}

void Employee::resetMonthlyBonus() {
    monthlyBonus = 0;
}

void Employee::displayCommonInfo() const {
    std::cout << "Ma nhan su: " << employeeId << '\n';
    std::cout << "Ho ten: " << fullName << '\n';
    std::cout << "Phong ban: " << department << '\n';
    std::cout << "Loai nhan su: " << getEmployeeType() << '\n';
}
