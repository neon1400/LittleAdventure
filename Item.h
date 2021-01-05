#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

enum type
{
    weapon,
    armor,
    potion
};

class Item
{
    private:
        string name_;
        int quantity_;
        type itemType_;
    public:
        Item(string name, int quantity, type itemType)
        {
            name_ = name;
            quantity_ = quantity;
            itemType_ = itemType;
        }
        int getQuantity()
        {//nowoœæ
            return quantity_;
        }
        bool substract()
        { // nowœæ
            if (quantity_ > 0)
            {
                quantity_--;
                return true;
            }
            return false;
        }
        void addToItem(int amount)
        {
            quantity_ += amount;
            if (quantity_ > 4)
            {
                quantity_ = 4;
            }
        }
};
