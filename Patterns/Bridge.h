#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>


class Implementor
{
public:
	virtual ~Implementor() {}
	virtual void Opration() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
	virtual void Opration() override
	{
		printf_s("Implement function A.\n");
	}
};

class ConcreteImplementorB : public Implementor
{
public:
	virtual void Opration() override
	{
		printf_s("Implement function B.\n");
	}
};

class Abstraction
{
public:
	void SetImplementor(Implementor* i_implementor)
	{
		implementor_ = i_implementor;
	}

	virtual void Opration() = 0;

protected:
	Implementor *implementor_;
};

class RefinedAbstraction : public Abstraction
{
public:
	virtual void Opration() override
	{
		implementor_->Opration();
	}
};


class BridgeTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Bridge\n");

		res &= testBridge();

		printf_s("End test Bridge\n\n");

		return res;
	}

private:
	bool testBridge()
	{
		Abstraction *abstraction = new RefinedAbstraction();

		Implementor *implementorA = new ConcreteImplementorA();
		Implementor *implementorB = new ConcreteImplementorB();

		abstraction->SetImplementor(implementorA);
		abstraction->Opration();

		abstraction->SetImplementor(implementorB);
		abstraction->Opration();

		delete implementorA;
		delete implementorB;
		delete abstraction;

		return true;
	}
};
