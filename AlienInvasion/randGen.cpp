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



randGen::randGen()
{
    srand((unsigned)time(NULL));
}

void randGen::getparameters(int* parameters)
{
    params = parameters;
}

void randGen::generateUnits(EarthArmy* EArmy, AlienArmy* aliens,int timestep)
{
    Unit* newUnit;


    int A = 1+(rand() % 100);

    if (A <= params[7])
    {
        for (int i = 0; i < params[0]; i++)
        {
            int B = 1 + (rand() % 100);
            int E_P = params[8] + (rand() % (params[9] - params[8] + 1));
            int E_H = params[10] + (rand() % (params[11] - params[10] + 1));
            int E_C = params[12] + (rand() % (params[13] - params[12] + 1));

           newUnit = createUnit(E_P, E_H, E_C, true, EArmy,aliens,timestep);

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

            newUnit = createUnit(A_P, A_H, A_C, false, EArmy,aliens,timestep);
   

        }
    }
}


Unit* randGen::createUnit(int H,int P,int C,bool is_E, EarthArmy * EArmy, AlienArmy * aliens,int timestep)
{
    Unit* newUnit;

    
    int B = 1 + (rand() % 100);

    if (is_E)
    {
        if (B <= params[1])
        {
             newUnit = new EarthSoldier(timestep, H, P, C);
             EArmy->addUnit(newUnit, UnitType::EarthSoldier);
        }
        else if (B <= params[2] + params[1])
        {
            newUnit = new EarthTank(timestep, H, P, C);
            EArmy->addUnit(newUnit, UnitType::Tank);
        }
        else
        {
            newUnit = new EarthGunnery(timestep, H, P, C);
            EArmy->addUnit(newUnit, UnitType::Gunnery);
        }
    }
    else
    {
        if (B <= params[4])
        {
             newUnit = new AlienSoldier(timestep, H, P, C);
             aliens->addUnit(newUnit, UnitType::AlienSoldier);
        }
        else if (B <= params[4] + params[6])
        {
             newUnit = new AlienMonster(timestep, H, P, C);
             aliens->addUnit(newUnit, UnitType::Monster);
        }
        else
        {
             newUnit = new AlienDrone(timestep, H, P, C);
             aliens->addUnit(newUnit, UnitType::Drone);
        }

    }

    return newUnit;
}