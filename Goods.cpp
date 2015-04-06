#include <iostream>
#include <string>
#include <list>
#include "Goods.h"

using namespace std;

Goods::Goods() {
    
}

int Goods::addGood(unsigned ID, string name, unsigned quantity, double price) {
    good newGood;
    newGood.goodID = ID;
    newGood.goodName = name;
    newGood.goodQuantity = quantity;
    newGood.goodPrice = price;
    
    goodsList.push_front(newGood);
    return goodsList.size();
}

int Goods::removeGood(unsigned ID) {
    for(iter = goodsList.begin(); iter != goodsList.end(); iter++) {
        if(iter->goodID == ID) {
            list<good>::iterator temp = iter;
            goodsList.erase(iter);
            iter = temp;
        }
    }
    
    return goodsList.size();
}

int Goods::displayList() {
    goodsList.sort(comparePrice);
    cout << "Displaying list of items, sorted by price:\n\n";
    for(iter = goodsList.begin(); iter != goodsList.end(); iter++) {
        cout << "ID: " << iter->goodID << '\n';
        cout << "Name: " << iter->goodName << '\n';
        cout << "Quantity: " << iter->goodQuantity << '\n';
        cout << "goodPrice: $" << iter->goodPrice << '\n';
        cout << '\n';
    }
    
    return goodsList.size();
}

bool Goods::updateGood(unsigned ID, string name, unsigned quantity, double price) {
    for(iter = goodsList.begin(); iter != goodsList.end(); iter++) {
        if(iter->goodID == ID) {
            iter->goodName = name;
            iter->goodQuantity = quantity;
            iter->goodPrice = price;
            return true;
        }
    }
    return false;
}

bool Goods::comparePrice(const Goods::good& first, const Goods::good& second) {
    return (first.goodPrice <= second.goodPrice);
}