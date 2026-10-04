#include "Payroll.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

Payroll::Payroll(const std::string& period) : period(period) {
    if (period.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("Payroll period must not be empty.");
    }
}

const std::string& Payroll::getPeriod() const {
    return period;
}

std::size_t Payroll::getEmployeeCount() const {
    return employees.size();
}

bool Payroll::addEmployee(std::unique_ptr<Employee> employee) {
    if (!employee || findEmployee(employee->getEmployeeId())) {
        return false;
    }

    employees.push_back(std::move(employee));
    return true;
}

Employee* Payroll::findEmployee(const std::string& employeeId) {
    for (const auto& employee : employees) {
        if (employee->getEmployeeId() == employeeId) {
            return employee.get();
        }
    }
    return nullptr;
}

const Employee* Payroll::findEmployee(const std::string& employeeId) const {
    for (const auto& employee : employees) {
        if (employee->getEmployeeId() == employeeId) {
            return employee.get();
        }
    }
    return nullptr;
}

double Payroll::calculateTotalPayroll() const {
    double total = 0;
    for (const auto& employee : employees) {
        total += employee->calculateGrossPay();
    }
    return total;
}

double Payroll::calculatePayrollByDepartment(const std::string& department) const {
    double total = 0;
    for (const auto& employee : employees) {
        if (employee->getDepartment() == department) {
            total += employee->calculateGrossPay();
        }
    }
    return total;
}

const Employee* Payroll::findHighestPaidEmployee() const {
    const Employee* highest = nullptr;
    for (const auto& employee : employees) {
        if (!highest || employee->calculateGrossPay() > highest->calculateGrossPay()) {
            highest = employee.get();
        }
    }
    return highest;
}

void Payroll::displayPayroll() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "BANG LUONG - " << period << '\n';

    if (employees.empty()) {
        std::cout << "Chua co nhan su.\n";
        std::cout << "Tong bang luong: 0.00\n";
        return;
    }

    for (const auto& employee : employees) {
        std::cout << "----------------------------------------\n";
        employee->displayPayrollInfo();
    }

    std::cout << "----------------------------------------\n";
    std::cout << "Tong bang luong: " << calculateTotalPayroll() << '\n';
}
