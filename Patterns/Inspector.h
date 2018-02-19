#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <vector>
#include <string>


class Observer
{
public:
	virtual ~Observer() {}
	virtual void Update() = 0;
};

class Subject
{
public:
	void Attach(Observer *i_observer)
	{
		observers_.push_back(i_observer);
	}

	void Detach(Observer *i_observer)
	{
		for (unsigned int i = 0; i < observers_.size(); ++i)
		{
			if (observers_[i] == i_observer)
			{
				observers_.erase(observers_.begin() + i);
				break;
			}
		}
	}

	void Notify()
	{
		for (unsigned int i = 0; i < observers_.size(); ++i)
		{
			observers_[i]->Update();
		}
	}

private:
	std::vector<Observer*> observers_;
};


class ConcreteSubject : public Subject
{
public:
	std::string subjectState_;
};


class ConcreteObserver : public Observer
{
public:
	ConcreteObserver(ConcreteSubject *i_subject, const char *i_name)
		: subject_(i_subject), name_(i_name)
	{
		subject_ = i_subject;
		name_ = i_name;
	}

	void Update()
	{
		observerState_ = subject_->subjectState_;
		printf_s("The observer's state of %s is %s.\n", name_.c_str(), observerState_.c_str());
	}

private:
	ConcreteSubject *subject_;
	std::string name_;
	std::string observerState_;
};



class JobStation : public Observer
{
public:
	virtual ~JobStation() {}
	virtual void Update() = 0;
};

class Customer : public Subject
{
public:
	std::string customerState_;
};

class Accountant : public JobStation
{
public:
	Accountant(Customer *i_customer)
	{
		customer_ = i_customer;
	}

	virtual void Update() override
	{
		if (customer_->customerState_ == "Paid")
		{
			printf_s("I am accountant, I will give the receipt.\n");
			accountantState_ = "Receipt";
		}
	}

private:
	std::string accountantState_;
	Customer* customer_;
};

class Cashier : public JobStation
{
public:
	Cashier(Customer *i_customer)
	{
		customer_ = i_customer;
	}

	virtual void Update() override
	{
		if (customer_->customerState_ == "Paid")
		{
			printf_s("I am cashier, I will record the deal.\n");
			cashierState_ = "Recorded.";
		}
	}

private:
	std::string cashierState_;
	Customer *customer_;
};

class Deliveryman : public JobStation
{
public:
	Deliveryman(Customer *i_customer)
	{
		customer_ = i_customer;
	}

	virtual void Update() override
	{
		if (customer_->customerState_ == "Paid")
		{
			printf_s("I am deliveryman, I will send the good.\n");
			delivierymanState_ = "Send";
		}
	}
private:
	std::string delivierymanState_;
	Customer *customer_;
};


class InspectorTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Inspector\n");

		res &= testInspector1();
		res &= testInspector2();

		printf_s("End test Inspector\n\n");

		return res;
	}

private:
	bool testInspector1()
	{
		printf_s("Start test Example1\n");

		ConcreteSubject *subject = new ConcreteSubject();

		Observer *observer1 = new ConcreteObserver(subject, "Observer A");
		Observer *observer2 = new ConcreteObserver(subject, "Observer B");
		Observer *observer3 = new ConcreteObserver(subject, "Observer C");

		subject->Attach(observer1);
		subject->Attach(observer2);
		subject->Attach(observer3);

		subject->subjectState_ = "Ready";
		subject->Notify();

		delete observer3;
		delete observer2;
		delete observer1;
		delete subject;

		printf_s("End test Example1\n\n");

		return true;
	}

	bool testInspector2()
	{
		printf_s("Start test Example2\n");

		Customer *subject = new Customer();

		JobStation *accountant = new Accountant(subject);
		JobStation *cashier = new Cashier(subject);
		JobStation *deliveryman = new Deliveryman(subject);
		subject->Attach(accountant);
		subject->Attach(cashier);
		subject->Attach(deliveryman);

		subject->customerState_ = "Paid";
		subject->Notify();

		delete accountant;
		delete cashier;
		delete deliveryman;
		delete subject;

		printf_s("End test Example2\n");

		return true;
	}
};
