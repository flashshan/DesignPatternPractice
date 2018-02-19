#pragma once

#include "../Interface/ITest.h"
#include <stdio.h>

class LazySingleton
{
public:
	static LazySingleton* GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new LazySingleton();
		}
		return instance_;
	}

private:
	static LazySingleton* instance_;
};

class HungrySingleton
{
public:
	static HungrySingleton* GetInstance()
	{
		return instance_;
	}

private:
	static HungrySingleton* instance_;
};


class SingletonTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Singleton\n");

		res &= testSingleton();

		printf_s("End test Singleton\n\n");

		return res;
	}

private:
	bool testSingleton()
	{
		LazySingleton* lazySingleton = LazySingleton::GetInstance();
		if (lazySingleton)
			printf_s("Get Lazy Singleton success.\n");
		else
			printf_s("Get Lazy Singleton failed.\n");

		HungrySingleton* hungrySingleton = HungrySingleton::GetInstance();
		if (hungrySingleton)
			printf_s("Get hungry Singleton success.\n");
		else
			printf_s("Get hungry Singleton failed.\n");

		return true;
	}
};
