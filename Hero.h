#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
// lokalne
#include "Wizard.h"
#include "Paladin.h"
#include "Rogue.h"
#include "Item.h"

using namespace std;

enum sex
{
    female,
    male

};

int d20Throw()
{
    return rand() % 20 + 1;
}

int d6Throw()
{
    return rand() % 6 + 1;
}

int rerollsLeft(int left, int rerolls)
{
    return (left - rerolls);
}

bool confirm()
{
    string decision;
    do
    {
        cin >> decision;
        cout << decision << endl;
    } while (decision != "N" && decision != "Y");
    if (decision == "N")
    {
        return false;
    }
    else
    {
        return true;
    }
}
/////////////////////////////////////////////////////////////////////////////////
////////////        HERO                /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


class Hero
{
    private:
        int haPE_;
        int maksHAPE_;
        int inteligence_;
        int strength_;
        int agility_;
        sex heroSex_;
        Classes* klasyPTR_;
        vector<Item> ekwipunek_;
    public:
        Hero();
        ~Hero() {cout << "usuwam postac" << endl;}
        void listAttribs();
        void assignClass(int);
        void getHeroClass();
        void rerollAttribs();
        void setInventory();//Set razem z utworzeniem klasy, myœlê trzeba omówiæ co tu isê znajdzie tak naprawdê, na poczatek placeholder potki.
        void addSpecificItem(int i);//zrobi siê rozpiskê co oznacza, który item. Tak bêdzie du¿o, du¿o szybciej ni¿ po koleji rozwa¿aæ ka¿dy przypadek.
        void consumePot(); //NOWOŒÆ
        bool subtractHP(int amount);
        int getHAPE();
        int checkPot();    //NOWOŒÆ
        void addPot(int amount);
        void addAgility(int amount);
        void addInteligence(int amount);
        void addStrength(int amount);

        int doAttack1();
        int doAttack2();
        int doAttack3();
        
        int getHP()
        {
            return haPE_;
        }
        int getInteligance()
        {
            return inteligence_;
        }
        int getStrength()
        {
            return strength_;
        }
        int getAgility()
        {
            return agility_;
        }
        int getSex()
        {
            if(heroSex_ == 1)
                return -1;
            else 
                return -2;
        }
        int getMaxHP()
        {
            return maksHAPE_;
        }

};
void Hero::listAttribs()
{
    cout << "HealthPoints:" << haPE_ << endl;
    cout << "Inteligence:" << inteligence_ << endl;
    cout << "Strength: " << strength_ << endl;
    cout << "Agility: " << agility_ << endl;
    cout << "Sex: ";
    if (heroSex_ == 1) cout << "male" << endl;
    else cout << "female" << endl;
}
Hero::Hero()
{
        srand(time(NULL));

        haPE_ = d20Throw() * 10;
        maksHAPE_ = haPE_;        
        inteligence_ = d20Throw();
        strength_ = d20Throw();
        agility_ = d20Throw();
        if (d6Throw() > 3)
        {
            heroSex_ = female;
        }
        else
        {
            heroSex_ = male;
        }
        listAttribs();
        setInventory();
}
void Hero::assignClass(int classChoice)
{
    cout << "Choose Your Class" << endl;
    cout << "1. Wizard" << endl;
    cout << "2. Paladin" << endl;
    cout << "3. Rogue" << endl;

    if (classChoice == 1)
    {
        klasyPTR_ = new Wizard;
    }
    if (classChoice == 2)
    {
        klasyPTR_ = new Paladin;
    }
    if (classChoice == 3)
    {
        klasyPTR_ = new Rogue;
    }
}
void Hero::getHeroClass()
{
    cout << klasyPTR_->getClass() << endl;
}

void Hero::rerollAttribs()
{
    srand(time(NULL));
        //rerolls++;
    haPE_ = d20Throw()*10;
    maksHAPE_ = haPE_;
    inteligence_ = d20Throw();
    strength_ = d20Throw();
    agility_ = d20Throw();
    if (d6Throw() > 3)
    {
        heroSex_ = female;
    }
    else
    {
        heroSex_ = male;
    }
    listAttribs();
}

int Hero::doAttack1()
{
    cout << 1 << endl;
    if (klasyPTR_->getClass() == "Wizard")
    {
        return (inteligence_ * (klasyPTR_->attack1())) / 100;
    }
    else
    {
        if (klasyPTR_->getClass() == "Paladin")
        {
            return (strength_ * (klasyPTR_->attack1())) / 100;
        }
        else
        {
            return (agility_ * (klasyPTR_->attack1())) / 100;
        }
    }
}
int Hero::doAttack2()
{
    if (klasyPTR_->getClass() == "Wizard")
    {
        return (inteligence_ * (klasyPTR_->attack2())) / 100;
    }
    else
    {
        if (klasyPTR_->getClass() == "Paladin")
        {
            return (strength_ * (klasyPTR_->attack2())) / 100;
        }
        else
        {
            return (agility_ * (klasyPTR_->attack2())) / 100;
        }
    }
}
int Hero::doAttack3()
{
    if (klasyPTR_->getClass() == "Wizard")
    {
        return (inteligence_ * (klasyPTR_->attack3())) / 100;
    }
    else
    {
        if (klasyPTR_->getClass() == "Paladin")
        {
            return (strength_ * (klasyPTR_->attack3())) / 100;
        }
        else
        {
            return (agility_ * (klasyPTR_->attack3())) / 100;
        }
    }
}

void Hero::setInventory()
{
    Item Potion("Healfpouszyn", 2, potion);
    ekwipunek_.push_back(Potion);
}
void Hero::consumePot()
{  //NOWOŒÆ
    if (ekwipunek_.front().substract())
    {
        haPE_ += 50;
        if (haPE_ > maksHAPE_)
        {
            haPE_ = maksHAPE_;
        }
    }
    else
    {
        //no nie ma wiêcej potuf no
    }
}

int Hero::checkPot()
{ //nowoœæ
    return ekwipunek_.front().getQuantity();
}

bool Hero::subtractHP(int amount)
{
    bool dead = false;
    haPE_ -= amount;
    if (haPE_ <= 0)
    {
        dead = true;
    }
    return dead;
}
int Hero::getHAPE()
{
    return haPE_;
}

void Hero::addPot(int amount)
{
    ekwipunek_.front().addToItem(amount);
}
void Hero::addAgility(int amount)
{
    agility_ += amount;
    if (agility_ > 20)
    {
        agility_ = 20;
    }
}
void Hero::addInteligence(int amount)
{
    inteligence_ += amount;
    if (inteligence_ > 20)
    {
        inteligence_ = 20;
    }
}
void Hero::addStrength(int amount)
{
    strength_ += amount;
    if (strength_ > 20)
    {
        strength_ = 20;
    }
}