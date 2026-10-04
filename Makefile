CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
SOURCES = Employee.cpp SalariedEmployee.cpp HourlyEmployee.cpp SalesEmployee.cpp Payroll.cpp
HEADERS = Employee.h SalariedEmployee.h HourlyEmployee.h SalesEmployee.h Payroll.h

all: payroll

payroll: main.cpp $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp $(SOURCES) -o payroll

test_payroll: tests/TestPayroll.cpp $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I. tests/TestPayroll.cpp $(SOURCES) -o test_payroll

test: test_payroll
	./test_payroll

.PHONY: all test
