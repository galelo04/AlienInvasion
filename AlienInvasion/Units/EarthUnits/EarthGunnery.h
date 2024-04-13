#pragma once
#include "../Unit.h".

class EarthGunnery : public Unit
{
	int Pri;
public:
	EarthGunnery(int jointime, int health, int power, int attackcapacity, int pri);
	virtual void Attack();
	int getPri();
};

