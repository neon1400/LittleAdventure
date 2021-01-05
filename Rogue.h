#pragma once
#include "Classes.h"

class Rogue :public Classes
{
    private:
    public:
    Rogue() {}
    ~Rogue() {}
    string getClass()
    {
        return "Rogue";
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