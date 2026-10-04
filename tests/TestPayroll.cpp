#include "HourlyEmployee.h"
#include "Payroll.h"
#include "SalariedEmployee.h"
#include "SalesEmployee.h"

#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

int totalTests = 0;
int passedTests = 0;

bool equalMoney(double actual, double expected) {
    return std::abs(actual - expected) < 0.001;
}

void check(bool condition, const std::string& name) {
    ++totalTests;
    if (condition) {
        ++passedTests;
        std::cout << "[PASS] ";
    } else {
        std::cout << "[FAIL] ";
    }
    std::cout << totalTests << ". " << name << '\n';
}

bool rejects(const std::function<void()>& action) {
    try {
        action();
    } catch (const std::invalid_argument&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

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

        check(equalMoney(payroll.findEmployee("E001")->calculateGrossPay(), 18000000),
              "E001 co thu nhap 18000000");
        check(equalMoney(payroll.findEmployee("E002")->calculateGrossPay(), 15500000),
              "E002 co thu nhap 15500000");
        check(equalMoney(payroll.findEmployee("E003")->calculateGrossPay(), 17500000),
              "E003 co thu nhap 17500000");
        check(equalMoney(payroll.findEmployee("E004")->calculateGrossPay(), 19000000),
              "E004 co thu nhap 19000000");
        check(equalMoney(payroll.calculateTotalPayroll(), 70000000),
              "Tong bang luong bang 70000000");
        check(equalMoney(payroll.calculatePayrollByDepartment("Hỗ trợ"), 33000000),
              "Tong phong Ho tro bang 33000000");
        check(payroll.findHighestPaidEmployee()->getEmployeeId() == "E004",
              "Nguoi co thu nhap cao nhat la E004");

        const Payroll& constPayroll = payroll;
        check(payroll.findEmployee("E002") != nullptr
                  && constPayroll.findEmployee("E002")->getFullName() == "Trần Thu Bình",
              "Tim nhan su qua bang luong thuong va const");
        check(payroll.findEmployee("UNKNOWN") == nullptr
                  && constPayroll.findEmployee("UNKNOWN") == nullptr,
              "Khong tim thay nhan su tra ve nullptr");
        check(equalMoney(payroll.calculatePayrollByDepartment("Unknown"), 0),
              "Phong ban khong ton tai co tong luong 0");

        SalariedEmployee salaried("S001", "An", 5000000);
        HourlyEmployee hourly("H001", "Binh", 100000);
        SalesEmployee sales("C001", "Dung", 8000000);

        check(salaried.getDepartment() == "Unassigned"
                  && equalMoney(salaried.getResponsibilityAllowance(), 0)
                  && equalMoney(salaried.getMonthlyBonus(), 0),
              "Constructor rut gon SalariedEmployee dung gia tri mac dinh");
        check(hourly.getDepartment() == "Unassigned"
                  && equalMoney(hourly.getWorkedHours(), 0)
                  && equalMoney(hourly.getMonthlyBonus(), 0),
              "Constructor rut gon HourlyEmployee dung gia tri mac dinh");
        check(sales.getDepartment() == "Unassigned"
                  && equalMoney(sales.getSalesRevenue(), 0)
                  && equalMoney(sales.getCommissionRate(), 0)
                  && equalMoney(sales.getMonthlyBonus(), 0),
              "Constructor rut gon SalesEmployee dung gia tri mac dinh");

        salaried.addBonus(100);
        salaried.addBonus(200, "Thuong co dinh");
        salaried.addBonus(0.1, 1000, "Thuong theo ty le");
        check(equalMoney(salaried.getMonthlyBonus(), 400),
              "Ba phien ban addBonus cong don dung");
        salaried.resetMonthlyBonus();
        check(equalMoney(salaried.getMonthlyBonus(), 0),
              "Dat lai thuong ve 0");

        HourlyEmployee h0("H0", "An", "Support", 100000, 0);
        HourlyEmployee h160("H160", "An", "Support", 100000, 160);
        HourlyEmployee h1605("H1605", "An", "Support", 100000, 160.5);
        HourlyEmployee h250("H250", "An", "Support", 100000, 250);

        check(equalMoney(h0.calculateGrossPay(), 0), "0 gio lam co thu nhap 0");
        check(equalMoney(h160.calculateGrossPay(), 16000000)
                  && equalMoney(h160.getOvertimeHours(), 0),
              "160 gio chua co tien lam them");
        check(equalMoney(h1605.calculateGrossPay(), 16075000),
              "160.5 gio tinh dung phan lam them");
        check(equalMoney(h250.calculateGrossPay(), 29500000),
              "250 gio la bien tren hop le");
        check(rejects([] { HourlyEmployee e("X", "An", "Support", 100000, -1); })
                  && rejects([] { HourlyEmployee e("X", "An", "Support", 100000, 250.1); }),
              "Tu choi gio lam am hoac vuot 250");

        check(rejects([] { SalariedEmployee e("", "An", 1); })
                  && rejects([] { SalariedEmployee e("X", "", 1); })
                  && rejects([] { SalariedEmployee e("X", "An", "", 1, 0); }),
              "Tu choi ma ho ten va phong ban rong");
        check(rejects([] { SalariedEmployee e(" \t", "An", 1); })
                  && rejects([] { SalariedEmployee e("X", " \n", 1); })
                  && rejects([] { SalariedEmployee e("X", "An", " \t", 1, 0); }),
              "Tu choi thong tin chi co khoang trang");
        check(rejects([] { SalariedEmployee e("X", "An", -1); })
                  && rejects([] { SalariedEmployee e("X", "An", "Support", 1, -1); })
                  && rejects([] { HourlyEmployee e("X", "An", -1); })
                  && rejects([] { SalesEmployee e("X", "An", -1); })
                  && rejects([] { SalesEmployee e("X", "An", "Sales", 1, -1, 0.1); }),
              "Tu choi luong phu cap don gia va doanh so am");

        SalesEmployee c0("C0", "Dung", "Sales", 8000000, 200000000, 0);
        SalesEmployee c30("C30", "Dung", "Sales", 8000000, 200000000, 0.3);
        check(equalMoney(c0.calculateGrossPay(), 8000000)
                  && equalMoney(c30.calculateGrossPay(), 68000000),
              "Hoa hong 0 va 0.3 deu hop le");
        check(rejects([] { SalesEmployee e("X", "An", "Sales", 1, 1, -0.01); })
                  && rejects([] { SalesEmployee e("X", "An", "Sales", 1, 1, 0.301); }),
              "Tu choi hoa hong ngoai khoang tu 0 den 0.3");

        check(rejects([&] { salaried.addBonus(0); })
                  && rejects([&] { salaried.addBonus(-1); }),
              "Tu choi thuong bang 0 hoac am");
        check(rejects([&] { salaried.addBonus(100, ""); })
                  && rejects([&] { salaried.addBonus(100, " \t"); }),
              "Tu choi ly do thuong rong");
        salaried.addBonus(0.5, 1000, "Thuong bien tren");
        check(equalMoney(salaried.getMonthlyBonus(), 500),
              "Ty le thuong 0.5 la hop le");
        check(rejects([&] { salaried.addBonus(0, 1000, "Thuong"); })
                  && rejects([&] { salaried.addBonus(-0.1, 1000, "Thuong"); })
                  && rejects([&] { salaried.addBonus(0.501, 1000, "Thuong"); }),
              "Tu choi ty le thuong ngoai khoang (0, 0.5]");
        check(rejects([&] { salaried.addBonus(0.1, 0, "Thuong"); })
                  && rejects([&] { salaried.addBonus(0.1, -1, "Thuong"); }),
              "Tu choi so tien tham chieu khong duong");
        check(rejects([&] { salaried.addBonus(0.1, 1000, ""); }),
              "Thuong theo ty le phai co ly do");
        check(equalMoney(salaried.getMonthlyBonus(), 500),
              "Thuong khong doi sau cac thao tac khong hop le");

        SalesEmployee updated("U001", "Dung", "Sales", 8000000, 200000000, 0.05);
        updated.setSalesRevenue(300000000);
        check(equalMoney(updated.calculateGrossPay(), 23000000),
              "Cap nhat doanh so lam thay doi thu nhap");
        check(rejects([&] { updated.setSalesRevenue(-1); })
                  && equalMoney(updated.getSalesRevenue(), 300000000),
              "Cap nhat doanh so am bi tu choi va giu gia tri cu");

        double nan = std::numeric_limits<double>::quiet_NaN();
        double infinity = std::numeric_limits<double>::infinity();
        check(rejects([&] { SalariedEmployee e("X", "An", nan); })
                  && rejects([&] { HourlyEmployee e("X", "An", "Support", 1, infinity); })
                  && rejects([&] { SalesEmployee e("X", "An", "Sales", 1, 1, nan); })
                  && rejects([&] { salaried.addBonus(nan); })
                  && rejects([&] { salaried.addBonus(0.1, infinity, "Thuong"); })
                  && rejects([&] { updated.setSalesRevenue(infinity); }),
              "Tu choi NaN va vo cuc trong du lieu so");

        bool duplicateAdded = payroll.addEmployee(std::unique_ptr<Employee>(
            new SalesEmployee("E001", "Nguoi khac", 1000000)));
        check(!duplicateAdded && payroll.getEmployeeCount() == 4
                  && equalMoney(payroll.calculateTotalPayroll(), 70000000),
              "Khong them trung ma giua cac loai nhan su");
        check(!payroll.addEmployee(std::unique_ptr<Employee>())
                  && payroll.getEmployeeCount() == 4,
              "Khong them con tro rong");

        Payroll empty("2026-10");
        std::ostringstream output;
        std::streambuf* original = std::cout.rdbuf(output.rdbuf());
        empty.displayPayroll();
        std::cout.rdbuf(original);
        check(equalMoney(empty.calculateTotalPayroll(), 0)
                  && equalMoney(empty.calculatePayrollByDepartment("Support"), 0)
                  && empty.findEmployee("X") == nullptr
                  && empty.findHighestPaidEmployee() == nullptr
                  && output.str().find("Chua co nhan su.") != std::string::npos,
              "Bang luong rong duoc xu ly hop ly");

        Payroll tied("2026-10");
        tied.addEmployee(std::unique_ptr<Employee>(new SalariedEmployee("T1", "An", 100)));
        tied.addEmployee(std::unique_ptr<Employee>(new SalariedEmployee("T2", "Binh", 100)));
        check(tied.findHighestPaidEmployee()->getEmployeeId() == "T1",
              "Dong hang thu nhap chon nhan su them truoc");

        payroll.findEmployee("E002")->addBonus(10000000);
        check(equalMoney(payroll.calculateTotalPayroll(), 80000000)
                  && equalMoney(payroll.calculatePayrollByDepartment("Hỗ trợ"), 43000000)
                  && payroll.findHighestPaidEmployee()->getEmployeeId() == "E002",
              "Tong hop luon dung thuong hien tai va loi goi da hinh");

        check(rejects([] { Payroll p(""); }) && rejects([] { Payroll p(" \t"); }),
              "Ky luong khong duoc rong");

        SalariedEmployee large("L1", "An", 0);
        double maximum = std::numeric_limits<double>::max();
        large.addBonus(maximum);
        bool overflowRejected = false;
        try {
            large.addBonus(maximum);
        } catch (const std::overflow_error&) {
            overflowRejected = true;
        }
        check(overflowRejected && large.getMonthlyBonus() == maximum,
              "Cong thuong tran so bi tu choi va giu gia tri cu");
    } catch (const std::exception& error) {
        std::cerr << "Loi kiem thu: " << error.what() << '\n';
        return 1;
    }

    std::cout << "\nKet qua: " << passedTests << '/' << totalTests << " PASS\n";
    return passedTests == totalTests ? 0 : 1;
}
