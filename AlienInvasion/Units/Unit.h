#pragma once
#include <iostream>

class Game;
enum class UnitType {
	EarthSoldier,
	Tank,
	Gunnery,
	HealingUnit,
	AlienSoldier,
	Monster,
	Drone
};

class Unit 
{

private:
	int ID;
	UnitType Type;
	int JoinTime;
	int firstAttackTime;
	int DestructionTime;
	int Health;
	int Power;
	int AttackCapacity;
	int numAttacks;
protected:
	static int last_Earth_Id;
	static int last_Alien_Id;
public:

	Unit(UnitType type,int id,  int jointime, int health, int power, int attackcapacity);
	virtual void Attack(Game * gameptr)=0;
	virtual UnitType getType() const;
	virtual int getID() const;
	virtual int getJoinTime() const;
	virtual int getTa() const;
	virtual void setTa(int Ta);
	virtual int getTd() const;
	virtual void setTd(int Td);
	virtual int getDf() const;
	virtual int getDd() const;
	virtual int getDb() const;
	virtual int getnumAttacks() const;
	virtual void incrementnumAttacks();
	virtual int getHealth() const;
	virtual int getPower() const;
	virtual int getAttackCapacity() const;
	virtual void decrementHealth(int damage);
	friend std::ostream& operator<<(std::ostream& stream, Unit* unit)
	{
		if (unit)
			stream << unit->ID;
		return stream;
	}
};
