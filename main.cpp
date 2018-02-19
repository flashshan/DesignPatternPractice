#include "Patterns/Factory.h"
#include "Patterns/Decorator.h"
#include "Patterns/Singleton.h"
#include "Patterns/Builder.h"
#include "Patterns/Prototype.h"
#include "Patterns/Strategy.h"
#include "Patterns/Proxy.h"
#include "Patterns/Composite.h"
#include "Patterns/Bridge.h"
#include "Patterns/TemplateMEthod.h"
#include "Patterns/Facade.h"
#include "Patterns/Command.h"
#include "Patterns/Inspector.h"
#include "Patterns/Adapter.h"
#include "Patterns/Memento.h"
#include "Patterns/Iterator.h"
#include "Patterns/COR.h"
#include "Patterns/Mediator.h"
#include "Patterns/Flyweight.h"
#include "Patterns/Interpreter.h"
#include "Patterns/Visitor.h"


int main()
{
	bool res = true;
	printf_s("Start test design patterns\n\n");

	FactoryTest	factoryTest;
	res &= factoryTest.RunTest();

	DecoratorTest decoratorTest;
	res &= decoratorTest.RunTest();

	SingletonTest singletonTest;
	res &= singletonTest.RunTest();

	BuilderTest builderTest;
	res &= builderTest.RunTest();

	PrototypeTest prototypeTest;
	res &= prototypeTest.RunTest();

	StrategyTest strategyTest;
	res &= strategyTest.RunTest();

	ProxyTest proxyTest;
	res &= proxyTest.RunTest();

	CompositeTest compositeTest;
	res &= compositeTest.RunTest();

	BridgeTest bridgeTest;
	res &= bridgeTest.RunTest();

	TemplateMethodTest templateMethodTest;
	res &= templateMethodTest.RunTest();

	FacadeTest facadeTest;
	res &= facadeTest.RunTest();

	CommandTest commandTest;
	res &= commandTest.RunTest();

	InspectorTest inspectorTest;
	res &= inspectorTest.RunTest();

	AdapterTest adapterTest;
	res &= adapterTest.RunTest();

	MementoTest mementoTest;
	res &= mementoTest.RunTest();

	IteratorTest iteratorTest;
	res &= iteratorTest.RunTest();

	CORTest	corTest;
	res &= corTest.RunTest();

	MediatorTest mediatorTest;
	res &= mediatorTest.RunTest();

	FlyweightTest flyweightTest;
	res &= flyweightTest.RunTest();

	InterpreterTest interpreterTest;
	res &= interpreterTest.RunTest();

	VisitorTest visitorTest;
	res &= visitorTest.RunTest();

	if(res)
		printf_s("Past all tests\n");
	else
		printf_s("Fail test\n");

#if defined _DEBUG
	_CrtDumpMemoryLeaks();		   // 2 byte for singletons
#endif // _DEBUG
	return 0;
}