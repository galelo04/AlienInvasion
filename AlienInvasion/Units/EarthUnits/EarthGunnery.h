#pragma once
#include "../Unit.h".
#include "../../DataStructures/Stack/ArrayStack.h".

class EarthGunnery : public Unit
{
public:
	EarthGunnery(int jointime, int health, int power, int attackcapacity);
	virtual void Attack();
};

