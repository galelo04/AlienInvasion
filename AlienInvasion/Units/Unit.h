#pragma once
#include <iostream>

class Game;
enum class UnitType {
	EarthSoldier =0,
	Tank,
	Gunnery,
	HealingUnit,
	AlienSoldier,
	Monster,
	Drone,
	SaverUnit
};

class Unit 
{

private:
	int ID;
	UnitType Type;
	int JoinTime;
	int firstAttackTime;
	int DestructionTime;
	int UMLJoiningTime;
	int Health;
	int Power;
	int AttackCapacity;
	int intialHealth;
	bool Attacked;
	bool infected;
	bool immuned;
protected:
	static int last_Earth_Id;
	static int last_Alien_Id;
	static int last_Ally_Id;
public:

	Unit(UnitType type,int id,  int jointime, int health, int power, int attackcapacity);
	virtual void Attack(Game* gameptr) = 0;
	virtual UnitType getType() const;
	virtual int getID() const;
	virtual int getJoinTime() const;
	virtual int getFirstAttackTime() const;
	virtual void setFirstAttackTime(int Ta);
	virtual int getDestructionTime() const;
	virtual void setDestructionTime(int Td);
	virtual int getUMLJoiningTime()const;
	virtual void setUMLJoiningTime(int TU);
	virtual bool IsAttacked() const;
	virtual void makeAttacked(bool makeatt);
	virtual int getHealth() const;
	virtual int getPower() const;
	virtual int getAttackCapacity() const;
	virtual void decrementHealth(int damage);
	virtual void heal(int imp) = 0;
	virtual int getIntialHealth() const;
	virtual void infect(bool state) ;
	virtual bool isInfected();
	virtual void immune(bool state);
	virtual bool isImmuned();
	friend std::ostream& operator<<(std::ostream& stream, Unit* unit)
	{
		if (unit)
		{
			stream << unit->ID;
			if (unit->isInfected())
				stream << "(#)";
		}
		return stream;
	}
};
