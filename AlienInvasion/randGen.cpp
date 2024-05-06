#include "randGen.h"
#include "iostream"
#include "Armies/EarthArmy/EarthArmy.h"
#include "Units/EarthUnits/EarthSoldier.h"
#include "Units/EarthUnits/EarthTank.h"
#include "Units/EarthUnits/EarthGunnery.h"
#include "Armies/AlienArmy/AlienArmy.h"
#include "Units/AlienUnits/AlienSoldier.h"
#include "Units/AlienUnits/AlienMonster.h"
#include "Units/AlienUnits/AlienDrone.h"
#include "Units/EarthUnits/HealingUnit.h"



randGen::randGen(Game* _gameptr)
{
    gameptr = _gameptr;
    srand((unsigned)time(NULL));
}

void randGen::getparameters(int* parameters)
{  
    params = parameters;
}

void randGen::generateUnits(int timestep)
{
    Unit* newUnit;
    int A = 1+(rand() % 100);

    if (A <= params[8])
    {
        for (int i = 0; i < params[0]; i++)
        {
            int B = 1 + (rand() % 100);
            int E_P = params[9] + (rand() % (params[10] - params[9] + 1));
            int E_H = params[11] + (rand() % (params[12] - params[11] + 1));
            int E_C = params[13] + (rand() % (params[14] - params[13] + 1));

           newUnit = createUnit(E_P, E_H, E_C, true,timestep);
           gameptr->getEarthArmy()->addUnit(newUnit);
        }
    }
    ////////////////////////////////////
    A = 1 + (rand() % 100);

    if (A <= params[8])
    {
        for (int i = 0; i < params[0]; i++)
        {
            int B = 1 + (rand() % 100);
            int A_P = params[15] + (rand() % (params[16] - params[15] + 1));
            int A_H = params[17] + (rand() % (params[18] - params[17] + 1));
            int A_C = params[19] + (rand() % (params[20] - params[19] + 1));

            newUnit = createUnit(A_P, A_H, A_C, false,timestep);
            gameptr->getAlienArmy()->addUnit(newUnit);
        }
    }
}


Unit* randGen::createUnit(int H,int P,int C,bool is_E,int timestep)
{
    Unit* newUnit;
    int B = 1 + (rand() % 100);

    if (is_E)
    {
        if (B <= params[1])
        {
             newUnit = new EarthSoldier(timestep, H, P, C);
        }
        else if (B <= params[2] + params[1])
        {
            newUnit = new EarthTank(timestep, H, P, C);
        }
        else if(B <= params[3]+ params[2]+ params[1])         // what is the condition
        {
            newUnit = new EarthGunnery(timestep, H, P, C);
        }
        else
        {
            newUnit = new HealingUnit(timestep, H, P, C);
        }
    }
    else
    {
        if (B <= params[4])
        {
             newUnit = new AlienSoldier(timestep, H, P, C);
        }
        else if (B <= params[4] + params[6])
        {
             newUnit = new AlienMonster(timestep, H, P, C,params[21]);
        }
        else
        {
             newUnit = new AlienDrone(timestep, H, P, C);
        }
    }
    return newUnit;
}