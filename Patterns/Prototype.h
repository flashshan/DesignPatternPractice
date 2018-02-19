#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>
#include <vector>

class WorkExperience
{
public:
	WorkExperience(const char* i_company, const char* i_position)
		: Company(i_company), Position(i_position) 
	{}

public:
	std::string Company;
	std::string Position;
};

class ICloneable {
public:
	virtual ~ICloneable() {}
	virtual ICloneable* ShallowCopyClone() = 0;
	virtual ICloneable* DeepCopyClone() = 0;
};


class Resume : public ICloneable
{
public:
	Resume() {}
	Resume(const char* i_name, const char* i_sex, int i_age)
		: name_(new std::string(i_name)), sex_(new std::string(i_sex)), age_(i_age),
		workExperiences_(new std::vector<WorkExperience* >()), isDeepCopied_(true)
	{
	}

	~Resume() 
	{
		if (isDeepCopied_)
		{
			delete name_;
			delete sex_;
			for (unsigned int i = 0; i < workExperiences_->size(); ++i)
				delete workExperiences_->at(i);
			delete workExperiences_;
		}
	}

public:
	void AddWorkExperience(const char* i_company, const char* i_position)
	{
		(*workExperiences_).push_back(new WorkExperience(i_company, i_position));
	}

	virtual ICloneable* ShallowCopyClone() override		 // use same container
	{
		Resume *newResume = new Resume();
		newResume->name_ = name_;
		newResume->sex_ = sex_;
		newResume->age_ = age_;
		newResume->workExperiences_ = workExperiences_;
		return newResume;
	}

	virtual ICloneable* DeepCopyClone()	override		  // make a new container
	{
		Resume *newResume = new Resume(name_->c_str(), sex_->c_str(), age_);
		
		for(unsigned int i = 0; i < workExperiences_->size(); ++i)
			newResume->workExperiences_->push_back(new WorkExperience(workExperiences_->at(i)->Company.c_str(), workExperiences_->at(i)->Position.c_str()));

		return newResume;
	}

	void PrintResume()
	{
		printf_s("Name: %s | Sex: %s | Age: %d\n", name_->c_str(), sex_->c_str(), age_);
		for (unsigned int i = 0; i < workExperiences_->size(); ++i)
		{
			printf_s("Work Experience %d: %s, %s\n", i, workExperiences_->at(i)->Company.c_str(), workExperiences_->at(i)->Position.c_str());
		}
	}
private:
	std::string* name_;
	std::string* sex_;
	int age_;
	std::vector<WorkExperience*> *workExperiences_;
	bool isDeepCopied_ = false;				// a marker used in destroy function
};



class PrototypeTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Prototype\n");

		res &= testPrototypeShallowCopy();
		res &= testPrototypeDeepCopy();

		printf_s("End test Prototype\n\n");

		return res;
	}

private:
	bool testPrototypeShallowCopy()
	{
		printf_s("Start test Prototype using shallow copy\n");

		Resume *myFirstResume = new Resume("Kevin Wang", "Male", 29);
		myFirstResume->AddWorkExperience("My First Company", "Software Engineer");

		Resume *mySecondResume = dynamic_cast<Resume*>(myFirstResume->ShallowCopyClone());
		mySecondResume->AddWorkExperience("My Second Company", "Software Engineer");

		Resume *myThirdResume = dynamic_cast<Resume*>(myFirstResume->ShallowCopyClone());
		myThirdResume->AddWorkExperience("My Third Company", "Senior Software Engineer");

		printf_s("First resume: \n");
		myFirstResume->PrintResume();
		printf_s("Second resume: \n");
		mySecondResume->PrintResume();
		printf_s("Third resume: \n");
		myThirdResume->PrintResume();

		delete myFirstResume;
		delete mySecondResume;
		delete myThirdResume;

		printf_s("End test Prototype using shallow copy\n\n");

		return true;
	}

	bool testPrototypeDeepCopy()
	{
		printf_s("Start test Prototype using deep copy\n");

		Resume *myFirstResume = new Resume("Kevin Wang", "Male", 29);
		myFirstResume->AddWorkExperience("My First Company", "Software Engineer");

		Resume *mySecondResume = dynamic_cast<Resume*>(myFirstResume->DeepCopyClone());
		mySecondResume->AddWorkExperience("My Second Company", "Software Engineer");

		Resume *myThirdResume = dynamic_cast<Resume*>(myFirstResume->DeepCopyClone());
		myThirdResume->AddWorkExperience("My Third Company", "Senior Software Engineer");

		printf_s("First resume: \n");
		myFirstResume->PrintResume();
		printf_s("Second resume: \n");
		mySecondResume->PrintResume();
		printf_s("Third resume: \n");
		myThirdResume->PrintResume();

		delete myFirstResume;
		delete mySecondResume;
		delete myThirdResume;

		printf_s("End test Prototype using deep copy\n\n");

		return true;
	}
};