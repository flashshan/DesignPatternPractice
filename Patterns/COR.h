#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>
#include <vector>


class Handler
{
public:
	virtual ~Handler() {}
	void SetNext(Handler *i_next)
	{
		next_ = i_next;
	}
	virtual void HandleRequest(int i_request) = 0;

protected:
	Handler *next_;
};

class ConcreteHandler1 : public Handler
{
public:
	virtual void HandleRequest(int i_request) override
	{
		if (i_request >= 0 && i_request < 10)
			printf_s("Handler 1 handle request: %d.\n", i_request);
		else if (next_ != nullptr)
			next_->HandleRequest(i_request);
	}
};

class ConcreteHandler2 : public Handler
{
public:
	virtual void HandleRequest(int i_request) override
	{
		if (i_request >= 10 && i_request < 20)
			printf_s("Handler 2 handle request: %d.\n", i_request);
		else if (next_ != nullptr)
			next_->HandleRequest(i_request);
	}
};

class ConcreteHandler3 : public Handler
{
public:
	virtual void HandleRequest(int i_request) override
	{
		if (i_request >= 20 && i_request < 30)
			printf_s("Handler 1 handle request: %d.\n", i_request);
		else if (next_ != nullptr)
			next_->HandleRequest(i_request);
	}
};



class CORTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Chain of responsibility\n");

		res &= testCOR();

		printf_s("End test Chain of responsibility\n\n");

		return res;
	}

private:
	bool testCOR()
	{
		Handler* handler1 = new ConcreteHandler1();
		Handler* handler2 = new ConcreteHandler2();
		Handler* handler3 = new ConcreteHandler3();

		handler1->SetNext(handler2);
		handler2->SetNext(handler3);

		std::vector<int> requests{ 2, 5, 14, 22, 17, 3, 27, 20 };

		for (unsigned int i = 0; i < requests.size(); ++i)
		{
			handler1->HandleRequest(requests[i]);
		}

		delete handler1;
		delete handler2;
		delete handler3;

		return true;
	}
};
