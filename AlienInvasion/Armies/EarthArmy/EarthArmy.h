#pragma once
#include "../Army.h"
#include "../../Units/EarthUnits/EarthSoldier.h"
#include "../../Units/EarthUnits/EarthGunnery.h"
#include "../../Units/EarthUnits/EarthTank.h"
#include "../../DataStructures/Stack/ArrayStack.h"
#include "../../DataStructures/Queue/LinkedQueue.h"
#include "../../DataStructures/Pri-Queue/priQueue.h"

class EarthArmy : public Army
{
private:
	LinkedQueue<Unit*>EarthSoldiers;
	ArrayStack<Unit*>EarthTanks;
	priQueue<Unit*>EarthGunneries;
	ArrayStack<Unit*>HealingList;
	priQueue <Unit*> UMLsoldiers;
	LinkedQueue<Unit*>UMLtanks;
	int InfectedSoldiers;
	int TotalinfES;
	int totalHealedES;
	int totalFixedET;
public:
	EarthArmy();
	virtual void addUnit(Unit* unit);
	virtual Unit* removeUnit(UnitType type);
	Unit* removefromUML(UnitType type);
	void addToUML(Unit* unit,int UT);
	virtual bool attack(Game* gameptr);

	virtual void infectionSpread();

	virtual void print();
	int getESCount();
	int getETCount();
	int getEGCount();
	int getInfESCount();

	void destroyUML(Game* gameptr);
	int getTotalFixedET();
	void incrementFixedET();
	int getTotalHealedES();
	void incrementHealedES();
	int getTotalinfES();
	void incrementInfES();
	void decrementInfES();
	int infES_P();

	~EarthArmy();
};

