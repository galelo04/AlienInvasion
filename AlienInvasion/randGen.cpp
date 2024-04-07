#include "randGen.h"
#include "iostream"

#include "Units/EarthUnits/EarthSoldier.h"
#include "Units/EarthUnits/EarthTank.h"
#include "Units/EarthUnits/EarthGunnery.h"

#include "Armies/AlienArmy/AlienArmy.h"
#include "Units/AlienUnits/AlienSoldier.h"
#include "Units/AlienUnits/AlienMonster.h"
#include "Units/AlienUnits/AlienDrone.h"

randGen::randGen(Game* gameptr)
{
    params = gameptr->getParams();
}


void randGen::createUnit(Game* gameptr)
{
    Unit* newUnit;

    srand((unsigned)time(NULL));
    int A = 1+(rand() % 100);

    if (A <= params[7])
    {
        for (int i = 0; i < params[0]; i++)
        {
            int B = 1 + (rand() % 100);
            int E_P = params[8] + (rand() % (params[9] - params[8] + 1));
            int E_H = params[10] + (rand() % (params[11] - params[10] + 1));
            int E_C = params[12] + (rand() % (params[13] - params[12] + 1));

            newUnit = genUnit(gameptr, E_P, E_H, E_C, true);

        }
    }
    ////////////////////////////////////
    A = 1 + (rand() % 100);

    if (A <= params[7])
    {
        for (int i = 0; i < params[0]; i++)
        {
            int B = 1 + (rand() % 100);
            int A_P = params[14] + (rand() % (params[15] - params[14] + 1));
            int A_H = params[16] + (rand() % (params[17] - params[16] + 1));
            int A_C = params[18] + (rand() % (params[19] - params[18] + 1));

            newUnit = genUnit(gameptr,A_P, A_H, A_C, false);
   

        }
    }
}

Unit* randGen::genUnit(Game* gameptr,int H,int P,int C,bool is_E)
{
    Unit* newUnit;

    srand((unsigned)time(NULL));
    int B = 1 + (rand() % 100);

    if (is_E)
    {
        if (B <= params[1])
        {
             newUnit = new EarthSoldier(gameptr->getTimeStep(), H, P, C);
        }
        else if (B <= params[2] + params[1])
        {
            newUnit = new EarthTank(gameptr->getTimeStep(), H, P, C);
        }
        else
        {
             newUnit = new EarthGunnery(gameptr->getTimeStep(), H, P, C);
        }
    }
    else
    {
        if (B <= params[4])
        {
             newUnit = new AlienSoldier(gameptr->getTimeStep(), H, P, C);
        }
        else if (B <= params[4] + params[6])
        {
             newUnit = new AlienMonster(gameptr->getTimeStep(), H, P, C);
        }
        else
        {
             newUnit = new AlienDrone(gameptr->getTimeStep(), H, P, C);
        }

    }

    return newUnit;
}