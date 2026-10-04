#ifndef HOURLY_EMPLOYEE_H
#define HOURLY_EMPLOYEE_H

#include "Employee.h"

class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    double workedHours;

public:
    HourlyEmployee(const std::string& employeeId, const std::string& fullName,
                   double hourlyRate);
    HourlyEmployee(const std::string& employeeId, const std::string& fullName,
                   const std::string& department, double hourlyRate, double workedHours);

    double getHourlyRate() const;
    double getWorkedHours() const;
    double getRegularHours() const;
    double getOvertimeHours() const;
    double calculateGrossPay() const override;
    std::string getEmployeeType() const override;
    void displayPayrollInfo() const override;
};

#endif
