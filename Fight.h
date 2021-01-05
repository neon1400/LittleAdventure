#pragma once
#include "Hero.h"
#include "Monster.h"
#include "Goblin.h"
#include "Ogr.h"
#include "Ork.h"
#include "Cyklop.h"

using namespace std;


int walka(Hero* Grabian, int monsterType)
{
    bool dead = false;
    bool turn = false;
    MonsterClasses* mon = new MonsterClasses;
    int attack = 0;
    int monAttack = 0;

    if (monsterType == 1)
    {
        mon = new Goblin;
    }
    else if(monsterType == 2)
    {
        mon = new Ork;
    }
    else if (monsterType == 3)
    {
        mon = new Ogr;
    }
    else
    {
        mon = new Cyklop;
    }


    while (!dead)
    {
        cout << "Hape Grabiana: " << Grabian->getHAPE() << endl;
        cout << "Poty Grabiana: "; Grabian->checkPot(); cout << endl;
        cout << "Typ Piaseckiego: " << mon->getMonster() << endl;
        cout << "Hape Piaseckiego: " << mon->getHAPE() << endl;
        if (turn == false)
        {
            cout << "atak od 1 do 3" << endl;

            do
            {
                cin >> attack;
                switch (attack)
                {
                case 1: { cout << "lmao" << endl;  dead = mon->subtractHP(Grabian->doAttack1()); }break;
                case 2: { cout << "lmao" << endl;  dead = mon->subtractHP(Grabian->doAttack2()); cout << "lmao" << endl; }break;
                case 3: { cout << "lmao" << endl;  dead = mon->subtractHP(Grabian->doAttack3()); }break;
                case 4: { cout << "lmao" << endl;  Grabian->consumePot(); }break;
                }
            } while (attack == 4);
        }
        else
        {
            cout << "dotarliœmy" << endl;
            monAttack = d20Throw();
            if (monAttack > 0 && monAttack < 8)
            {
                dead = Grabian->subtractHP(mon->doAttack1());
            }
            else
            {
                if (monAttack > 7 && monAttack < 20)
                {
                    dead = Grabian->subtractHP(mon->doAttack2());
                }
                else
                {
                    dead = Grabian->subtractHP(mon->doAttack3());
                }
            }
        }
        turn = !turn;

    }
    return 0;
}



