#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>
#include <vector>


class Mediator;

class College {
public:
	College(Mediator *i_mediator)
		: mediator_(i_mediator)
	{}

	virtual void Send(const char* i_message) = 0;
	virtual void Notify(const char *i_message) = 0;

protected:
	Mediator *mediator_;
};

class Mediator
{
public:
	virtual void Send(const char *i_message, College *i_college) = 0;
	virtual void AddCollege(College *i_college) = 0;

protected:
	std::vector<College *> colleges_;
};

class ConcreteCollege1 : public College
{
public:
	ConcreteCollege1(Mediator *i_mediator)
		: College(i_mediator)
	{
		i_mediator->AddCollege(this);
	}

	virtual void Send(const char* i_message) override
	{
		mediator_->Send(i_message, this);
	}

	virtual void Notify(const char *i_message) override
	{
		printf_s("College 1 get message: %s.\n", i_message);
	}
};

class ConcreteCollege2 : public College
{
public:
	ConcreteCollege2(Mediator *i_mediator)
		: College(i_mediator)
	{
		i_mediator->AddCollege(this);
	}

	virtual void Send(const char* i_message) override
	{
		mediator_->Send(i_message, this);
	}

	virtual void Notify(const char *i_message) override
	{
		printf_s("College 2 get message: %s.\n", i_message);
	}
};

class ConcreteMediator : public Mediator
{
public:
	void AddCollege(College *i_college)
	{
		colleges_.push_back(i_college);
	}

	virtual void Send(const char *i_message, College *i_college) override
	{
		for (unsigned int i = 0; i < colleges_.size(); ++i)
		{
			if (colleges_[i] != i_college)
			{
				colleges_[i]->Notify(i_message);
			}
		}
	}
};


class MediatorTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Mediator\n");

		res &= testMediator();

		printf_s("End test Mediator\n\n");

		return res;
	}

private:
	bool testMediator()
	{
		ConcreteMediator *mediator = new ConcreteMediator();
		ConcreteCollege1 *college1 = new ConcreteCollege1(mediator);
		ConcreteCollege2 *college2 = new ConcreteCollege2(mediator);
	    
		college1->Send("Has you eat?");
		college2->Send("I have!");
		
		delete college1;
		delete college2;
		delete mediator;

		return true;
	}
};
