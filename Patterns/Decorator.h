#pragma once

#include "../Interface/ITest.h"

#include <stdio.h>

class Equipment
{
public:
	virtual ~Equipment() {}
	virtual void Attack() = 0;
};

class Soldier : public Equipment
{
public:
	Soldier() {}

	virtual void Attack() override
	{
		printf_s("Attack with riot!\n");
	}
};

class EquipDecorator : public Equipment
{
public:
	void SetComponent(Equipment* i_equipment)
	{
		equipment_ = i_equipment;
	}

	virtual void Attack()
	{
		if (equipment_ != nullptr)
		{
			equipment_->Attack();
		}
	}

private:
	Equipment *equipment_;
};

class RifleEquipment : public EquipDecorator
{
public:
	virtual void Attack() override
	{
		EquipDecorator::Attack();

		printf_s("Rifle shoot!\n");
	}
};

class MachineGunEquipment : public EquipDecorator
{
public:
	virtual void Attack() override
	{
		EquipDecorator::Attack();

		printf_s("Machine gun shoot\n");
	}
};

class RocketGunEquipment : public EquipDecorator
{
public:
	virtual void Attack() override
	{
		EquipDecorator::Attack();

		printf_s("Rocket shoot......!\n");
	}
};


class DecoratorTest : public ITest {
public:
	virtual bool RunTest() override
	{
		bool res = true;

		printf_s("Start test Decorator\n");

		res &= testDecorator();

		printf_s("End test Decorator\n\n");

		return res;
	}

private:
	bool testDecorator()
	{
		Soldier *soldier = new Soldier();

		RifleEquipment *rifle = new RifleEquipment();
		MachineGunEquipment *machineGun = new MachineGunEquipment();
		RocketGunEquipment *rocketGun = new RocketGunEquipment();

		rifle->SetComponent(soldier);
		machineGun->SetComponent(rifle);
		rocketGun->SetComponent(machineGun);

		rocketGun->Attack();

		delete rocketGun;
		delete machineGun;
		delete rifle;
		delete soldier;

		return true;
	}
};