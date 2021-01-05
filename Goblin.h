#pragma once
//#include "Monster.h"

using namespace std;

class Goblin :public MonsterClasses
{
    private:
    int haPE_ = 50;//jeba? balans full CSGO stajl
    int strength_ = 5;
    int agility_ = 20;
    public:
    Goblin() {}
    ~Goblin() {}
    string getMonster()
    {
        return "Goblin";
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