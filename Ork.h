#pragma once
#include "Monster.h"

using namespace std;

class Ork :public MonsterClasses
{
    private:
    int haPE_ = 100;
    int strength_ = 10;
    int agility_ = 15;
    public:
    Ork() {}
    ~Ork() {}
    string getMonster()
    {
        return "Ork";
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
    { //NOWOŒÆ
        cout << 1 << endl;
        return ((300 * strength_) / 100);
    }
    int doAttack2()
    { //NOWOŒÆ
        return ((450 * strength_) / 100);
    }
    int doAttack3()
    { //Atak 3 TO ZAWSZE KRYT //NOWOŒÆ
        return ((1000 * agility_) / 100);
    }
    bool subtractHP(int amount)
    { //NOWOŒÆ
        bool dead = false;
        haPE_ -= amount;
        if (haPE_ <= 0)
        {
            dead = true;
        }
        return dead;
    }

};