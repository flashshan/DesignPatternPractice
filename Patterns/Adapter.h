#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>

class Adaptee
{
public:
	void SpecificRequest()
	{
		printf_s("This is a special request.\n");
	}
};

class Target
{
public:
	virtual ~Target() {}
	virtual void Request()
	{
		printf_s("This is a common request\n");
	}
};

class Adapter : public Target
{
public:
	virtual void Request() override
	{
		adaptee->SpecificRequest();
	}

private:
	Adaptee *adaptee;
};


class AdapterTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Adapter\n");

		res &= testAdapter();

		printf_s("End test Adapter\n\n");

		return res;
	}

private:
	bool testAdapter()
	{
		Target *target = new Adapter();
		target->Request();
		
		delete target;
		return true;
	}
};
