#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <map>
#include <string>


class Flyweight
{
public:
	virtual ~Flyweight() {}
	virtual void Operation(int i_number) = 0;
};

class ConcreteFlyweight : public Flyweight
{
public:
	virtual void Operation(int i_number) 
	{
		printf_s("Shared Concrete flyweight: %d.\n", i_number);
	}
};

class UnsharedConcreteFlyweight : public Flyweight
{
public:
	virtual void Operation(int i_number)
	{
		printf_s("Unshared Concrete flyweight: %d.\n", i_number);
	}
};

class FlyweightFactory
{
public:
	FlyweightFactory()
	{
		flyweightsMap_.insert(std::make_pair('X', new ConcreteFlyweight()));
		flyweightsMap_.insert(std::make_pair('Y', new ConcreteFlyweight()));
		flyweightsMap_.insert(std::make_pair('Z', new ConcreteFlyweight()));
	}
	~FlyweightFactory()
	{
		for (auto it = flyweightsMap_.begin(); it != flyweightsMap_.end(); ++it)
		{
			delete it->second;
		}
	}

	Flyweight* GetFlyweight(const char i_flyweightKey)
	{
		auto it = flyweightsMap_.find(i_flyweightKey);
		if (it != flyweightsMap_.end())
			return it->second;
		else
			return nullptr;
	}

private:
	std::map<char, Flyweight *> flyweightsMap_;
};



class FlyweightTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Fly weight.\n");

		res &= testFlyweight();

		printf_s("End test Fly weight.\n\n");

		return res;
	}

private:
	bool testFlyweight()
	{
		int number = 22;
		
		FlyweightFactory *flyweightFactory = new FlyweightFactory();
		Flyweight *flyweight1 = flyweightFactory->GetFlyweight('X');
		flyweight1->Operation(--number);

		Flyweight *flyweight2 = flyweightFactory->GetFlyweight('Y');
		flyweight1->Operation(--number);

		Flyweight *flyweight3 = flyweightFactory->GetFlyweight('Z');
		flyweight1->Operation(--number);

		UnsharedConcreteFlyweight *unsharedFlyweight = new UnsharedConcreteFlyweight();
		unsharedFlyweight->Operation(--number);

		delete unsharedFlyweight;
		delete flyweightFactory;

		return true;
	}
};
