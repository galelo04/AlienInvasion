#pragma once
#include "../Unit.h".

class SaverUnit:public Unit
{
private:
public:
	SaverUnit(int jointime, int health, int power, int attackcapacity);
	 virtual void Attack(Game* gameptr);
	 virtual void heal(int imp) {};
};

