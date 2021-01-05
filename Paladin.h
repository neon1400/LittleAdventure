#pragma once
#include "Classes.h"

class Paladin :public Classes
{
    private:
    public:
    Paladin() {}
    ~Paladin() {}
    string getClass()
    {
        return "Paladin";
    }
    int attack1()
    {
        return 700;
    }
    int attack2()
    {
        return 300;
    }
    int attack3()
    {
        return 20000;
    }
};