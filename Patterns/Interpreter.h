#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <string>
#include <vector>


class InterpretContext
{
public:
	std::string input_;
	std::string output_;
};

class AbstractExpression
{
public:
	virtual ~AbstractExpression() {}
	virtual void Interpret(InterpretContext *i_context) = 0;
};

class TerminalExpression : public AbstractExpression
{
public:
	virtual void Interpret(InterpretContext *i_context)
	{
		printf_s("Terminal expression.\n");
	}
};

class NonterminalExpression : public AbstractExpression
{
public:
	virtual void Interpret(InterpretContext *i_context)
	{
		printf_s("Nonterminal expression.\n");
	}
};


class InterpreterTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Interpreter.\n");

		res &= testInterpreter();

		printf_s("End test Interpreter.\n\n");

		return res;
	}

private:
	bool testInterpreter()
	{
		InterpretContext *context = new InterpretContext();

		std::vector<AbstractExpression *> expressions;
		expressions.push_back(new TerminalExpression());
		expressions.push_back(new NonterminalExpression());
		expressions.push_back(new TerminalExpression());

		for (unsigned int i = 0; i < expressions.size(); ++i)
			expressions[i]->Interpret(context);
		
		for (unsigned int i = 0; i < expressions.size(); ++i)
			delete expressions[i];
		delete context;
		return true;
	}
};
