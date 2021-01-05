#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>


using namespace std;
class MonsterClasses
{
    private:
    public:
        MonsterClasses() {}
        ~MonsterClasses() {}
        virtual string getMonster()
        {
            return "0";
        }
        virtual int getHAPE()
        {
            return 0;
        }
        virtual int getStrength()
        {
            return 0;
        }
        virtual int getAgility()
        {
            return 0;
        }
        virtual int doAttack1()
        {
            return 0;
        }
        virtual int doAttack2()
        {
            return 0;
        }
        virtual int doAttack3()
        {
            return 0;
        }
        virtual bool subtractHP(int amount)
        {
            return 0;
        }
};
