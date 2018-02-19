#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>

class SubSystemOne
{
public:
	void MethodeOne()
	{
		printf_s("Sub System first method.\n");
	}
};

class SubSystemTwo
{
public:
	void MethodTwo()
	{
		printf_s("Sub System second method.\n");
	}
};

class SubSystemThree
{
public:
	void MethodThree()
	{
		printf_s("Sub System third method.\n");
	}
};

class SubSystemFour
{
public:
	void MethodFour()
	{
		printf_s("Sub System fourth method.\n");
	}
};

class Facade
{
public:
	void MethodA()
	{
		printf_s("Method group A----\n");
		one.MethodeOne();
		two.MethodTwo();
		four.MethodFour();
	}

	void MethodB()
	{
		printf_s("Method group B----\n");
		two.MethodTwo();
		three.MethodThree();
	}

private:
	SubSystemOne one;
	SubSystemTwo two;
	SubSystemThree three;
	SubSystemFour four;
};


class Employee
{
public:
	std::string name_;
	int age_;
	int salary_;
};

class EmployeeDataAccess
{
public:
	void SaveEmployee(Employee *i_employee)
	{
		printf_s("Save employee to database.\n");
	}

	void DeleteEmployee(Employee *i_employee)
	{
		printf_s("Remove employee from database.\n");
	}
};

class SalaryDataAccess
{
public:
	void SaveSalary(int i_salary)
	{
		printf_s("Save salary to database.\n");
	}

	void DeleteSalary(int i_salary)
	{
		printf_s("Remove salary from database.\n");
	}
};

class DataAccess
{
public:
	void SaveEmployee(Employee *i_employee)
	{
		employeeDataAccess.SaveEmployee(i_employee);
		salaryDataAccess.SaveSalary(i_employee->salary_);
	}

	void RemoveEmployee(Employee *i_employee)
	{
		salaryDataAccess.DeleteSalary(i_employee->salary_);
		employeeDataAccess.DeleteEmployee(i_employee);
	}

private:
	EmployeeDataAccess employeeDataAccess;
	SalaryDataAccess salaryDataAccess;
};



class FacadeTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Facade\n");

		res &= testFacade();
		res &= testFacade2();

		printf_s("End test Facade\n\n");

		return res;
	}

private:
	bool testFacade()
	{
		printf_s("Start test Example 1\n");

		Facade facade;
		facade.MethodA();
		facade.MethodB();

		printf_s("End test Example 1\n\n");
		return true;
	}

	bool testFacade2()
	{
		printf_s("Start test Example 2\n");

		Employee *employee = new Employee();
		employee->salary_ = 3000;
		employee->name_ = "Wang Kevin";
		employee->age_ = 22;
		
		DataAccess dataAccess;

		dataAccess.SaveEmployee(employee);
		dataAccess.RemoveEmployee(employee);
		delete employee;

		printf_s("End test Example 2\n\n");
		return true;
	}
};
