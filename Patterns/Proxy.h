#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>


class ISubject
{
public:
	virtual ~ISubject() {}
	virtual void Function1() = 0;
	virtual void Function2() = 0;
};

class RealSubject : public ISubject
{
public:
	virtual void Function1() override
	{
		printf_s("This is the first function.\n");
	}

	virtual void Function2() override
	{
		printf_s("This is the second function.\n");
	}
};

class Proxy : public ISubject
{
public:
	Proxy()
	{
		realSubject_ = new RealSubject();
	}
	~Proxy()
	{
		delete realSubject_;
	}

	void Function1()
	{
		realSubject_->Function1();
	}

	void Function2()
	{
		realSubject_->Function2();
	}

private:
	RealSubject* realSubject_;
};


class ProxyTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Proxy\n");

		res &= testProxy();

		printf_s("End test Proxy\n\n");

		return res;
	}

private:
	bool testProxy()
	{
		ISubject *subjectProxy = new Proxy();

		subjectProxy->Function1();
		subjectProxy->Function2();

		delete subjectProxy;
		return true;
	}
};
