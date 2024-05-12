#include "randGen.h"
#include "iostream"
#include "Armies/EarthArmy/EarthArmy.h"
#include "Units/EarthUnits/EarthSoldier.h"
#include "Units/EarthUnits/EarthTank.h"
#include "Units/EarthUnits/EarthGunnery.h"
#include "Units/EarthUnits/HealingUnit.h"

#include "Armies/AlienArmy/AlienArmy.h"
#include "Units/AlienUnits/AlienSoldier.h"
#include "Units/AlienUnits/AlienMonster.h"
#include "Units/AlienUnits/AlienDrone.h"

#include "Armies/AllyArmy/AllyArmy.h"
#include "Units/SaverUints/SaverUnit.h"



randGen::randGen(Game* _gameptr)
{
    allyLimit = false;
    gameptr = _gameptr;
    srand((unsigned)time(NULL));
    earth_limit = false;
    alien_limit = false;
    generateSU = false;

}

void randGen::getparameters(int parameters[], int size)
{  
    for (int i = 0; i < size; i++)
    {
        params[i] = parameters[i];
    }
}

void randGen::EA_help()
{
   /* int infP = gameptr->getEarthArmy()->infES_P();
    cout << "Inf% before generation " << infP << endl;
    */
    if (generateSU == false)
    {
        if (gameptr->getEarthArmy()->infES_P() >= params[28])
            generateSU = true;
    }
    else
    {
        if (gameptr->getAllyArmy()->withdrawal(gameptr))
            generateSU = false;
    }

}

void randGen::generateUnits(int timestep)
{
    EA_help();

    Unit* newUnit;
    int A = 1+(rand() % 100);

    if (A <= params[8] && !earth_limit)
    {
        for (int i = 0; i < params[0]; i++)
        {

            int E_P = params[9] + (rand() % (params[10] - params[9] + 1));
            int E_H = params[11] + (rand() % (params[12] - params[11] + 1));
            int E_C = params[13] + (rand() % (params[14] - params[13] + 1));

           newUnit = createUnit(E_P, E_H, E_C, eartharmy,timestep);
           gameptr->getEarthArmy()->addUnit(newUnit);
        }
    }
    ////////////////////////////////////
    A = 1 + (rand() % 100);

    if (A <= params[8] && !alien_limit)
    {
        for (int i = 0; i < params[0]; i++)
        {

            int A_P = params[15] + (rand() % (params[16] - params[15] + 1));
            int A_H = params[17] + (rand() % (params[18] - params[17] + 1));
            int A_C = params[19] + (rand() % (params[20] - params[19] + 1));

            newUnit = createUnit(A_P, A_H, A_C, alienarmy,timestep);
            gameptr->getAlienArmy()->addUnit(newUnit);
        }
    }
    ////////////////////////
    if (generateSU && !allyLimit)
    {
        for (int i = 0; i < params[0]; i++)
        {
            int SU_P = params[21] + (rand() % (params[22] - params[21] + 1));
            int SU_H = params[23] + (rand() % (params[24] - params[23] + 1));
            int SU_C = params[25] + (rand() % (params[26] - params[25] + 1));

            newUnit = createUnit(SU_P, SU_H, SU_C, allyarmy, timestep);
            gameptr->getAllyArmy()->addUnit(newUnit);
            
        }
    }
}




Unit* randGen::createUnit(int H,int P,int C,ArmyType type,int timestep)
{
    Unit* newUnit = nullptr; 
    int B = 1 + (rand() % 100);

    if (type==eartharmy)
    {
        if (B <= params[1])
        {
             newUnit = new EarthSoldier(timestep, H, P, C);
        }
        else if (B <= params[2] + params[1])
        {
            newUnit = new EarthTank(timestep, H, P, C);
        }
        else if(B <= params[3]+ params[2]+ params[1])         
        {
            newUnit = new EarthGunnery(timestep, H, P, C);
        }
        else
        {
            newUnit = new HealingUnit(timestep, H, P, C);
        }
        if (newUnit->getID() == 999)
            earth_limit = true;
    }
    else if(type==alienarmy)
    {
        if (B <= params[5])
        {
             newUnit = new AlienSoldier(timestep, H, P, C);
        }

        else if (B <= params[5] + params[6])
        {
             newUnit = new AlienMonster(timestep, H, P, C,params[28]);

        }
        else
        {
             newUnit = new AlienDrone(timestep, H, P, C);
        }
        if (newUnit->getID() == 2999)
            alien_limit = true;
    }
    else if(type==allyarmy)
    {
        newUnit = new SaverUnit(timestep, H, P, C);
        if (newUnit->getID() == 4250)
            allyLimit = true;
    }

    return newUnit;
}