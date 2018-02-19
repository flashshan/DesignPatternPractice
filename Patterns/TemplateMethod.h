#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <vector>

class AbstractClass
{
public:
	virtual ~AbstractClass() {}
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;

	void TemplateMethod()
	{
		PrimitiveOperation1();
		PrimitiveOperation2();
		printf_s("Done the method.\n");
	}
};

class ConcreteClassA : public AbstractClass
{
public:
	virtual void PrimitiveOperation1() override
	{
		printf_s("Implement operation 1 in concrete class A.\n");
	}

	virtual void PrimitiveOperation2() override
	{
		printf_s("Implement operation 2 in Concrete class A.\n");
	}
};

class ConcreteClassB : public AbstractClass
{
public:
	virtual void PrimitiveOperation1() override
	{
		printf_s("Implement operation 1 in Concrete class B.\n");
	}

	virtual void PrimitiveOperation2() override
	{
		printf_s("Implement operation 2 in Concrete class B.\n");
	}
};



class BubbleSorter
{
protected:
	int DoSort()
	{
		operations_ = 0;
		if (length_ <= 1)
		{
			return operations_;
		}

		for (int nextToLast = length_ - 2; nextToLast >= 0; nextToLast--)
		{
			for (int index = 0; index <= nextToLast; index++)
			{
				if (OutOfOrder(index))
				{
					Swap(index);
				}

				++operations_;
			}
		}

		return operations_;
	}

	virtual void Swap(int index) = 0;
	virtual bool OutOfOrder(int index) = 0;

protected:
	int operations_ = 0;
	int length_ = 0;
};


class IntBubbleSorter : public BubbleSorter
{
public:
	int Sort(std::vector<int> &i_array)
	{
		array_ = &i_array;
		length_ = array_->size();
		return DoSort();
	}

	virtual void Swap(int index) override
	{
		int temp = array_->at(index);
		array_->at(index) = array_->at(index + 1);
		array_->at(index + 1) = temp;
	}

	virtual bool OutOfOrder(int index) override
	{
		return (array_->at(index) > array_->at(index + 1));
	}

private:
	std::vector<int> *array_;
};

class FloatBubbleSorter : public BubbleSorter
{
public:
	int Sort(std::vector<float> &i_array)
	{
		array_ = &i_array;
		length_ = array_->size();
		return DoSort();
	}

	virtual void Swap(int index) override
	{
		float temp = array_->at(index);
		array_->at(index) = array_->at(index + 1);
		array_->at(index + 1) = temp;
	}

	virtual bool OutOfOrder(int index) override
	{
		return (array_->at(index) > array_->at(index + 1));
	}

private:
	std::vector<float> *array_;
};



class TemplateMethodTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Template Method\n");

		res &= testTemplateMethod();
		res &= testSortMethod();

		printf_s("End test Template Method\n\n");

		return res;
	}

private:
	bool testTemplateMethod()
	{
		printf_s("Start test example 1\n");

		AbstractClass* concreteClassA = new ConcreteClassA();
		AbstractClass* concreteClassB = new ConcreteClassB();
		
		concreteClassA->TemplateMethod();
		concreteClassB->TemplateMethod();

		printf_s("End test example 1\n\n");

		delete concreteClassA;
		delete concreteClassB;

		return true;
	}

	bool testSortMethod()
	{
		printf_s("Start test example 2\n");

		std::vector<int> intArray{5, 3, 12, 8, 10};
		printf_s("Origin int number:\n");
		for (unsigned int i = 0; i < intArray.size(); ++i)
		{
			printf_s("%d ", intArray[i]);
		}
		printf_s("\n");

		IntBubbleSorter intSorter;
		intSorter.Sort(intArray);
		printf_s("After sort int numbers:\n");
		for (unsigned int i = 0; i < intArray.size(); ++i)
		{
			printf_s("%d ", intArray[i]);
		}
		printf_s("\n");


		std::vector<float> floatArray{ 5.0f, 3.0f, 12.0f, 8.0f, 10.0f };
		printf_s("Origin float number:\n");
		for (unsigned int i = 0; i < floatArray.size(); ++i)
		{
			printf_s("%f ", floatArray[i]);
		}
		printf_s("\n");

		FloatBubbleSorter floatSorter;
		floatSorter.Sort(floatArray);
		printf_s("After sort float numbers:\n");
		for (unsigned int i = 0; i < floatArray.size(); ++i)
		{
			printf_s("%f ", floatArray[i]);
		}
		printf_s("\n");

		printf_s("End test example 2\n\n");
		return true;
	}
};
