#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>
#include <vector>

class Visitor;
class ConcreteElementA;
class ConcreteElementB;

class Element
{
public:
	virtual ~Element() {};
	virtual void Accept(Visitor* i_visitor) = 0;
};	  

class Visitor {
public:
	virtual void VisitConcreteElementA(ConcreteElementA *i_concreteElementA) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB *i_concreteElementB) = 0;
};

class ConcreteElementA : public Element
{
public:
	virtual void Accept(Visitor* i_visitor) override
	{
		i_visitor->VisitConcreteElementA(this);
	}
};

class ConcreteElementB : public Element
{
public:
	virtual void Accept(Visitor* i_visitor) override
	{
		i_visitor->VisitConcreteElementB(this);
	}
};
	 
class ConcreteVisitor1 : public Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *i_concreteElementA) override
	{
		printf_s("Visitor1 visit elementA.\n");
	}
	virtual void VisitConcreteElementB(ConcreteElementB *i_concreteElementB) override
	{
		printf_s("Visitor1 visit elementB.\n");
	}
};

class ConcreteVisitor2 : public Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *i_concreteElementA) override
	{
		printf_s("Visitor2 visit elementA.\n");
	}
	virtual void VisitConcreteElementB(ConcreteElementB *i_concreteElementB) override
	{
		printf_s("Visitor2 visit elementB.\n");
	}
};

class ObjectStructure
{
public:
	void Attach(Element *i_element)
	{
		elements.push_back(i_element);
	}
	void Detach(Element *i_element)
	{
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			if (elements[i] == i_element)
			{
				elements.erase(elements.begin() + i);
				break;
			}
		}
	}
	void Accept(Visitor *i_visitor)
	{
		for (unsigned int i = 0; i < elements.size(); ++i)
		{
			elements[i]->Accept(i_visitor);
		}
	}

private:
	std::vector<Element *> elements;
};



class VisitorTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Visitor\n");

		res &= testVisitor();

		printf_s("End test Visitor\n\n");

		return res;
	}

private:
	bool testVisitor()
	{
		ObjectStructure objectStructure;
		
		Element *elementA = new ConcreteElementA();
		Element *elementB = new ConcreteElementB();
		objectStructure.Attach(elementA);
		objectStructure.Attach(elementB);

		Visitor *visitor1 = new ConcreteVisitor1();
		Visitor *visitor2 = new ConcreteVisitor2();

		objectStructure.Accept(visitor1);
		objectStructure.Accept(visitor2);

		delete visitor1;
		delete visitor2;
		delete elementA;
		delete elementB;

		return true;
	}
};
