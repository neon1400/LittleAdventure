#pragma once
#include "Monster.h"

using namespace std;

class Ogr :public MonsterClasses
{
    private:
    int haPE_ = 150;
    int strength_ = 15;
    int agility_ = 10;
    public:
    Ogr() {}
    ~Ogr() {}
    string getMonster()
    {
        return "Ogr";
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
    { //NOWO��
        cout << 1 << endl;
        return ((300 * strength_) / 100);
    }
    int doAttack2()
    { //NOWO��
        return ((450 * strength_) / 100);
    }
    int doAttack3()
    { //Atak 3 TO ZAWSZE KRYT //NOWO��
        return ((1000 * agility_) / 100);
    }
    bool subtractHP(int amount)
    { //NOWO��
        bool dead = false;
        haPE_ -= amount;
        if (haPE_ <= 0)
        {
            dead = true;
        }
        return dead;
    }
};