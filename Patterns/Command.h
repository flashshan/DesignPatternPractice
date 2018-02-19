#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>


class Receiver
{
public:
	void Action()
	{
		printf_s("Execute request!\n");
	}
};

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void Execute() = 0;
};

class ConcereteCommand : public ICommand
{
public:
	ConcereteCommand(Receiver *i_receiver)
	{
		receiver_ = i_receiver;
	}

	virtual void Execute() override
	{
		receiver_->Action();
	}
private:
	Receiver *receiver_;
};


class Invoker
{
public:
	void SetCommand(ICommand *i_command)
	{
		command_ = i_command;
	}

	void ExecuteCommand()
	{
		command_->Execute();
	}

private:
	ICommand *command_;
};




class Account
{
public:
	void MoneyIn(float i_amount)
	{
		totalAmount_ += i_amount;
	}

	void MoneyOut(float i_amount)
	{
		totalAmount_ -= i_amount;
	}

	float GetTotalAmout()
	{
		return totalAmount_;
	}

private:
	float totalAmount_ = 0.0f;
};

class AccountCommand
{
public:
	AccountCommand(Account *i_account)
	{
		account_ = i_account;
	}
	virtual ~AccountCommand() {}

	virtual void Execute() = 0;

protected:
	Account *account_;
};

class MoneyInCommand : public AccountCommand
{
public:
	MoneyInCommand(Account *i_account, float i_amount)
		: AccountCommand(i_account)
	{
		amount_ = i_amount;
	}

	virtual void Execute() override
	{
		account_->MoneyIn(amount_);
	}

private:
	float amount_;
};

class MoneyOutCommand : public AccountCommand
{
public:
	MoneyOutCommand(Account *i_account, float i_amount)
		: AccountCommand(i_account)
	{
		amount_ = i_amount;
	}
	
	virtual void Execute() override
	{
		account_->MoneyOut(amount_);
	}

private:
	float amount_;
};

class AccountInvoker
{
public:
	void SetCommand(AccountCommand *i_command)
	{
		command_ = i_command;
	}

	void ExecuteCommand()
	{
		command_->Execute();
	}

private:
	AccountCommand *command_;
};



class CommandTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Command\n");

		res &= testCommand1();
		res &= testCommand2();

		printf_s("End test Command\n\n");

		return res;
	}

private:
	bool testCommand1()
	{
		printf_s("Start test Example 1\n");

		Receiver *receiver = new Receiver();
		ICommand *command = new ConcereteCommand(receiver);
		Invoker *invoker = new Invoker();

		invoker->SetCommand(command);
		invoker->ExecuteCommand();

		delete invoker;
		delete command;
		delete receiver;

		printf_s("End test Example 1\n\n");
		return true;
	}

	bool testCommand2()
	{
		printf_s("Start test Example 2\n");

		Account *account = new Account();
		AccountCommand *commandIn = new MoneyInCommand(account, 500);
		
		AccountInvoker invoker;

		invoker.SetCommand(commandIn);
		invoker.ExecuteCommand();
		printf_s("The current amount is %f\n", account->GetTotalAmout());

		AccountCommand *commandIn2 = new MoneyInCommand(account, 500);
		invoker.SetCommand(commandIn2);
		invoker.ExecuteCommand();
		printf_s("The current amount is %f\n", account->GetTotalAmout());

		AccountCommand *commandOut = new MoneyOutCommand(account, 300);
		invoker.SetCommand(commandOut);
		invoker.ExecuteCommand();
		printf_s("The current amount is %f\n", account->GetTotalAmout());

		delete commandOut;
		delete commandIn2;
		delete commandIn;
		delete account;


		printf_s("End test Example 2\n\n");
		return true;
	}
};
