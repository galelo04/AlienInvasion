#pragma once
//
//private:
//	LinkedQueue<AlienSoldier*> List;
//	int count;
//public:
//	AlienSoldier();
//	virtual bool Add(Unit* newUnit);
//	virtual bool Remove(Unit* removedUnit);
//	virtual void PrintList();




//bool AlienSoldier::Add(Unit* newUnit)
//{
//    AlienSoldier* newalienSoldier = dynamic_cast<AlienSoldier*>(newUnit);
//    if (newalienSoldier != nullptr)
//    {
//        List.enqueue(newalienSoldier);
//        return true;
//    }
//    return false;
//}
//bool AlienSoldier::Remove(Unit* removedUnit)
//{
//    AlienSoldier* deletedalienSoldier = dynamic_cast<AlienSoldier*>(removedUnit);
//    if (!List.isEmpty() && deletedalienSoldier != nullptr)
//    {
//        List.dequeue(deletedalienSoldier);
//        return true;
//    }
//    return false;
//}
//
//void AlienSoldier::PrintList()
//{
//}
