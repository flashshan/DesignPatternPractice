#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>

class Person
{
public:
	void PrintPerson()
	{
		printf_s("Head: %s\nBody: %s\nArm: %s\nLeg: %s\n", Head.c_str(), Body.c_str(), Arm.c_str(), Leg.c_str());
	}

public:
	std::string Head;
	std::string Body;
	std::string Arm;
	std::string Leg;
};

class Builder
{
public:
	virtual ~Builder() {}

	void SetPerson(Person *i_person)
	{
		person_ = i_person;
	}

	virtual void BuildHead() = 0;
	virtual void BuildBody() = 0;
	virtual void BuildArm() = 0;
	virtual void BuildLeg() = 0;
protected:
	Person* person_;
};


class ThinPersonBuilder : public Builder
{
public:
	virtual void BuildHead() override
	{
		person_->Head = "Thin head";
	}

	virtual void BuildBody() override
	{
		person_->Body = "Thin body";
	}

	virtual void BuildArm() override
	{
		person_->Arm = "Thin arm";
	}

	virtual void BuildLeg() override
	{
		person_->Leg = "Thin leg";
	}
};

class FatPersonBuilder : public Builder
{
public:
	virtual void BuildHead() override
	{
		person_->Head = "Fat head";
	}

	virtual void BuildBody() override
	{
		person_->Body = "Fat body";
	}

	virtual void BuildArm() override
	{
		person_->Arm = "Fat arm";
	}

	virtual void BuildLeg() override
	{
		person_->Leg = "Fat Leg";
	}
};


class PersonDirector
{
public:
	void SetBuilder(Builder* i_personBuilder)
	{
		builder_ = i_personBuilder;
	}

	void BuildPerson(Person *&i_person)
	{
		builder_->SetPerson(i_person);
		builder_->BuildHead();
		builder_->BuildBody();
		builder_->BuildArm();
		builder_->BuildLeg();
	}

private:
	Builder* builder_;
};


class BuilderTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Builder\n");

		res &= testBuilder();

		printf_s("End test Builder\n\n");

		return res;
	}

private:
	bool testBuilder()
	{
		PersonDirector personDirector;

		ThinPersonBuilder *thinBuilder = new ThinPersonBuilder();
		FatPersonBuilder *fatBuilder = new FatPersonBuilder();

		Person *thinPerson = new Person(), *fatPerson = new Person();

		personDirector.SetBuilder(thinBuilder);
		personDirector.BuildPerson(thinPerson);

		personDirector.SetBuilder(fatBuilder);
		personDirector.BuildPerson(fatPerson);

		printf_s("Print thin person: \n");
		thinPerson->PrintPerson();
		printf_s("Print fat person: \n");
		fatPerson->PrintPerson();		

		delete thinPerson;
		delete fatPerson;
		delete thinBuilder;
		delete fatBuilder;

		return true;
	}
};