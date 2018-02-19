#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>


class Memento
{
public:
	Memento(const char *i_state)
		: state_(i_state)
	{
	}

public:
	std::string state_;
};

class Originator
{
public:
	Memento *CreateMemento()
	{
		return new Memento(state_.c_str());
	}
	void SetMemento(Memento *i_memento)
	{
		state_ = i_memento->state_;
	}
	void Show()
	{
		printf_s("State = %s\n", state_.c_str());
	}

public:
	std::string state_;
};

class Caretaker {
public:
	Memento *memento_;
};



class MementoTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Memento\n");

		res &= testMemento();

		printf_s("End test Memento\n\n");

		return res;
	}

private:
	bool testMemento()
	{
		Originator *originator = new Originator();
		originator->state_ = "On";
		originator->Show();

		Caretaker *careTaker = new Caretaker();
		careTaker->memento_ = originator->CreateMemento();

		originator->state_ = "Off";
		originator->Show();

		originator->SetMemento(careTaker->memento_);
		originator->Show();

		delete careTaker->memento_;
		delete careTaker;
		delete originator;

		return true;
	}
};
