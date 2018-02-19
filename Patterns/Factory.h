#pragma once

#include "../Interface/ITest.h"
#include <stdio.h>

#pragma region SimpleFactory

class Product
{
public:
	virtual ~Product() {}
	virtual void Opration() = 0;
};

class ConcreteProductA : public Product
{
public:
	virtual void Opration() override
	{
		printf_s("Product A Operation.\n");
	}
};

class ConcreteProductB : public Product
{
public:
	virtual void Opration() override
	{
		printf_s("Product B Operation.\n");
	}
};

class SimpleProductFactory
{
public:
	enum class ProductType {
		ETypeA,
		ETypeB,
	};
	static Product* CreateProduct(ProductType i_productType)
	{
		Product* product = nullptr;
		switch (i_productType)
		{
		case ProductType::ETypeA:
			return new ConcreteProductA();
		case ProductType::ETypeB:
			return new ConcreteProductB();
		default:
			return nullptr;
		}
	}
};
#pragma endregion

#pragma region FactoryMethod
// Factory Method
class Creator
{
public:
	virtual ~Creator() {}
	virtual Product* CreateProduct() = 0;
};

class ProductACreator : public Creator
{
public:
	virtual Product* CreateProduct() override
	{
		return new ConcreteProductA();
	}
};

class ProductBCreator : public Creator
{
public:
	virtual Product* CreateProduct() override
	{
		return new ConcreteProductB();
	}
};
#pragma endregion

#pragma region AbstractFactory
class IUser
{
public:
	virtual ~IUser() {}
	virtual void InitUser() = 0;
};

class IEmployee
{
public:
	virtual ~IEmployee() {}
	virtual void InitEmployee() = 0;
};

class SqlUser : public IUser
{
public:
	virtual void InitUser() override
	{
		printf_s("Init a sql user\n");
	}
};

class AccessUser : public IUser
{
public:
	virtual void InitUser() override
	{
		printf_s("Init a access user\n");
	}

};

class SqlEmployee : public IEmployee
{
public: 
	virtual void InitEmployee() override
	{
		printf_s("Init a sql employee\n");
	}
};

class AccessEmployee : public IEmployee
{
public:
	virtual void InitEmployee() override
	{
		printf_s("Init a access employee\n");
	}
};


class IDatabaseFactory
{
public:
	virtual ~IDatabaseFactory() {}
	virtual IEmployee* CreateEmployee() = 0;
	virtual IUser* CreateUser() = 0;
};

class SqlServerDatabaseFactory : public IDatabaseFactory
{
public:
	virtual IEmployee* CreateEmployee() override
	{
		return new SqlEmployee();
	}

	virtual IUser* CreateUser() override
	{
		return new SqlUser();
	}
};

class AccessDatabaseFactory : public IDatabaseFactory
{
public:
	virtual IEmployee* CreateEmployee() override
	{
		return new AccessEmployee();
	}

	virtual IUser* CreateUser() override
	{
		return new AccessUser();
	}
};
#pragma endregion


class FactoryTest : public ITest{
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Factory\n");

		res &= testSimpleFactory();
		res &= testFactoryMethod();
		res &= testAbstractFactory();

		printf_s("End test Factory\n\n");

		return res;
	}

private:
	bool testSimpleFactory()
	{
		printf_s("Start Test Simple Factory\n");

		Product *productA = SimpleProductFactory::CreateProduct(SimpleProductFactory::ProductType::ETypeA);
		Product *productB = SimpleProductFactory::CreateProduct(SimpleProductFactory::ProductType::ETypeB);
		productA->Opration();
		productB->Opration();
		delete productA;
		delete productB;

		printf_s("End Test Simple Factory\n\n");
		return true;
	}

	bool testFactoryMethod()
	{
		printf_s("Start Test Factory Method\n");

		ProductACreator aCreator;
		ProductBCreator bCreator;
		Product *productA = aCreator.CreateProduct();
		Product *productB = bCreator.CreateProduct();
		productA->Opration();
		productB->Opration();

		delete productA;
		delete productB;

		printf_s("End Test Factory Method\n\n");
		return true;
	}

	bool testAbstractFactory()
	{
		printf_s("Start Test Abstract Factory\n");

		SqlServerDatabaseFactory sqlDatabaseFactory;
		AccessDatabaseFactory accessDatabaseFactory;

		IUser *user1 = sqlDatabaseFactory.CreateUser();
		user1->InitUser();
		IUser *user2 = accessDatabaseFactory.CreateUser();
		user2->InitUser();

		IEmployee *employee1 = sqlDatabaseFactory.CreateEmployee();
		employee1->InitEmployee();
		IEmployee *employee2 = accessDatabaseFactory.CreateEmployee();
		employee2->InitEmployee();

		delete user1;
		delete user2;
		delete employee1;
		delete employee2;

		printf_s("End Test Abstract Factory\n\n");
		return true;
	}
};



