#include "HourlyEmployee.h"
#include "Payroll.h"
#include "SalariedEmployee.h"
#include "SalesEmployee.h"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>

int main() {
    try {
        Payroll payroll("2026-09");

        std::unique_ptr<Employee> e1(new SalariedEmployee(
            "E001", "Nguyễn Minh An", "Đào tạo", 15000000, 2000000));
        e1->addBonus(1000000);
        payroll.addEmployee(std::move(e1));

        std::unique_ptr<Employee> e2(new HourlyEmployee(
            "E002", "Trần Thu Bình", "Hỗ trợ", 100000, 150));
        e2->addBonus(500000, "Ho tro khach hang");
        payroll.addEmployee(std::move(e2));

        std::unique_ptr<Employee> e3(new HourlyEmployee(
            "E003", "Lê Hoàng Chi", "Hỗ trợ", 100000, 170));
        payroll.addEmployee(std::move(e3));

        std::unique_ptr<Employee> e4(new SalesEmployee(
            "E004", "Phạm Quốc Dũng", "Kinh doanh", 8000000, 200000000, 0.05));
        e4->addBonus(0.02, 50000000, "Hoan thanh chi tieu");
        payroll.addEmployee(std::move(e4));

        payroll.displayPayroll();
        std::cout << "Tong phong Ho tro: "
                  << payroll.calculatePayrollByDepartment("Hỗ trợ") << '\n';

        const Employee* highest = payroll.findHighestPaidEmployee();
        if (highest) {
            std::cout << "Nhan su co thu nhap cao nhat: "
                      << highest->getEmployeeId() << " - " << highest->getFullName()
                      << " - " << highest->calculateGrossPay() << '\n';
        }

        const Employee* found = payroll.findEmployee("E002");
        if (found) {
            std::cout << "\nKET QUA TIM NHAN SU E002\n";
            found->displayPayrollInfo();
        }
    } catch (const std::exception& error) {
        std::cerr << "Loi: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
