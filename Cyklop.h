#pragma once
#include "Monster.h"

using namespace std;

class Cyklop :public MonsterClasses
{
    private:
    int haPE_ = 200;
    int strength_ = 20;
    int agility_ = 5;
    public:
    Cyklop() {}
    ~Cyklop() {}
    string getMonster()
    {
        return "Cyklop";
    }
    int getHAPE()
    {
        return haPE_;
    }
    int getStrength()
    {
        return strength_;
    }
    int getAgility()
    {
        return agility_;
    }
    int doAttack1()
    {
        cout << 1 << endl;
        return ((300 * strength_) / 100);
    }
    int doAttack2()
    {
        return ((450 * strength_) / 100);
    }
    int doAttack3()
    { //Atak 3 TO ZAWSZE KRYT
        return ((1000 * agility_) / 100);
    }
    bool subtractHP(int amount)
    {
        bool dead = false;
        haPE_ -= amount;
        if (haPE_ <= 0)
        {
            dead = true;
        }
        return dead;
    }
};


