#pragma once
#include <string>

using namespace std;

class Classes
{
    private:

    public:
        Classes() {}
        ~Classes() {}
        virtual string getClass()
        {
            return "0";
        }
        virtual int attack1() = 0;
        virtual int attack2() = 0;
        virtual int attack3() = 0;
};