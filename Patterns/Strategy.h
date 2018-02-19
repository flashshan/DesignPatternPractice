#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>

class Stratege
{
public:
	virtual ~Stratege() {}
	virtual void Algorithm() = 0;
};

class ConcreteStrategeA : public Stratege
{
public:
	virtual void Algorithm() override
	{
		printf_s("This is strategy A\n");
	}
};

class ConcreteStrategeB : public Stratege
{
public:
	virtual void Algorithm() override
	{
		printf_s("This is strategy B\n");
	}
};

class Context
{
public:
	void SetStrategy(Stratege* i_stratege)
	{
		stratege_ = i_stratege;
	}

	void ExecuteAlgorithm()
	{
		stratege_->Algorithm();
	}

private:
	Stratege *stratege_;
};

class StrategyTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Strategy\n");

		res &= testStrategy();

		printf_s("End test Strategy\n\n");

		return res;
	}

private:
	bool testStrategy()
	{
		Context context;
		ConcreteStrategeA *strategyA = new ConcreteStrategeA();
		ConcreteStrategeB *strategyB = new ConcreteStrategeB();
		context.SetStrategy(strategyA);
		context.ExecuteAlgorithm();

		context.SetStrategy(strategyB);
		context.ExecuteAlgorithm();

		delete strategyA;
		delete strategyB;

		return true;
	}
};
