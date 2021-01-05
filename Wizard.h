#pragma once
#include "Classes.h"

class Wizard :public Classes
{ //Marek lol
    private:
    public:
    Wizard() {}
    ~Wizard() {}
    string getClass()
    {
        return "Wizard";
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