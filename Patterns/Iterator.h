#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <vector>
#include <string>

template<typename T>
class Iterator
{
public:
	virtual ~Iterator() {}
   	virtual T* First() = 0;
	virtual T* Next() = 0;
	virtual bool IsDone() = 0;
	virtual T* CurrentItem() = 0;
};

template<typename T>
class Aggregate 
{
public:
	virtual ~Aggregate() {}
	virtual Iterator<T>* CreateIterator() = 0;
};

template<typename T> class ConcreteAggregate;

template<typename T>
class ConcreteIterator : public Iterator<T>
{
public:
	ConcreteIterator(ConcreteAggregate<T> *i_aggregate)
	{
		aggregate_ = i_aggregate;
	}

	virtual T* First() override
	{
		return (*aggregate_)[0];
	}
	virtual T* Next() override
	{
		if (++current_ < aggregate_->GetCount())
			return (*aggregate_)[current_];
		else
			return nullptr;
	}
	virtual bool IsDone() override
	{
		return current_ >= aggregate_->GetCount() ? true : false;
	}
	virtual T* CurrentItem() override
	{
		return (*aggregate_)[current_];
	}
private:
	ConcreteAggregate<T> *aggregate_;
	int current_ = 0;
};


template<typename T>
class ConcreteAggregate : public Aggregate<T>
{
public:
	virtual Iterator<T>* CreateIterator() override
	{
		return new ConcreteIterator<T>(this);
	}
	
	void AddItem(T i_item)
	{
		items_.push_back(i_item);
	}

	int GetCount()
	{
		return items_.size();
	}

	T* operator[](int i_index)
	{
		return &(items_[i_index]);
	}

private:
	std::vector<T> items_;
};



class IteratorTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Iterator\n");

		res &= testIterator();

		printf_s("End test Iterator\n\n");

		return res;
	}

private:
	bool testIterator()
	{
		ConcreteAggregate<std::string> *container = new ConcreteAggregate<std::string>();
		container->AddItem(std::string("A bird."));
		container->AddItem(std::string("A Dog."));
		container->AddItem(std::string("A Pack."));
		container->AddItem(std::string("A worker."));
		container->AddItem(std::string("A desk."));
		
		Iterator<std::string> *iterator = container->CreateIterator();
		//std::string *firstItem = iterator->First();

		while (!iterator->IsDone())
		{
			printf_s("%s, please buy a ticket.\n", (*iterator->CurrentItem()).c_str());
			iterator->Next();
		}

		delete iterator;
		delete container;

		return true;
	}
};
