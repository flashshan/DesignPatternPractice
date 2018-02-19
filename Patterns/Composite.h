#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>
#include <vector>


class Component
{
public:
	virtual ~Component() {}
	Component(const char* i_name)
	{
		name_ = i_name;
	}

	virtual void Add(Component* i_component) = 0;
	virtual void Remove(Component* i_component) = 0;
	virtual void Display(int i_level) = 0;

protected:
	std::string name_;
};

class Leaf : public Component
{
public:
	Leaf(const char *i_name)
		: Component(i_name)
	{}

	virtual void Add(Component *i_component) override
	{
		printf_s("Can not add a component to a leaf.\n");
	}

	virtual void Remove(Component *i_component) override
	{
		printf_s("Can not remove a component to a leaf.\n");
	}

	virtual void Display(int i_level) override
	{
		printf_s("-%d %s\n", i_level, name_.c_str());
	}
};

class Composite : public Component
{
public:
	Composite(const char* i_name)
		: Component(i_name)
	{ }

	void Add(Component* i_component)
	{
		children.push_back(i_component);
	}

	void Remove(Component* i_component)
	{
		for (unsigned int i = 0; i < children.size(); ++i)
		{
			if (children[i] == i_component)
			{
				children.erase(children.begin() + i);
				break;
			}
		}
	}

	void Display(int i_level)
	{
		printf_s("-%d %s\n", i_level, name_.c_str());

		for(unsigned int i = 0; i < children.size(); ++i)
		{
			children[i]->Display(i_level + 2);
		}
	}

private:
	std::vector<Component *> children;
};


class CompositeTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Composite\n");

		res &= testComposite();

		printf_s("End test Composite\n\n");

		return res;
	}

private:
	bool testComposite()
	{
		Composite root("Root");
		Leaf leaf1("Leaf A in Root");
		Leaf leaf2("Leaf B in Root");
		root.Add(&leaf1);
		root.Add(&leaf2);

		Composite branchX("Branch X in Root");
		Composite branchY("Branch Y in Root");
		root.Add(&branchX);
		root.Add(&branchY);

		Leaf leaf3("Leaf A in Branch X");
		branchX.Add(&leaf3);

		Composite branchZ("Branch Z in Branch X");
		branchX.Add(&branchZ);

		Leaf leaf4("Leaf in Branch Y");
		Leaf leaf5("Leaf in Branch Z");
		branchY.Add(&leaf4);
		branchZ.Add(&leaf5);

		root.Display(1);
		return true;
	}
};
