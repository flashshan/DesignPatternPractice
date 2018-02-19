#pragma once 

class ITest {
public:
	virtual ~ITest() {}

	virtual bool RunTest() = 0;
};