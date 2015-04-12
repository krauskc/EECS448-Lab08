#include <iostream>
#include <string>
#include <list>
#include "Goods.h"

using namespace std;

Goods::Goods() {
    goodCount = 0;
}

unsigned Goods::addGood(unsigned ID, string name, unsigned quantity, double price) {
    good* newGood = new good();
    newGood->goodID = ID;
    newGood->goodName = name;
    newGood->goodQuantity = quantity;
    newGood->goodPrice = price;
    
    goodsList.push_front(*newGood);
    goodCount++;
    return goodsList.size();
}

unsigned Goods::removeGood(unsigned ID) {
    int removed = 0;
    for(iter = goodsList.begin(); iter != goodsList.end(); iter++) {
        if(iter->goodID == ID) {
            list<good>::iterator temp = iter;
            goodsList.erase(iter);
            iter = temp;
            removed++;
        }
    }
    
    //goodCount -= removed;
    return goodsList.size();
}

unsigned Goods::displayList() {
    goodsList.sort(comparePrice);
    cout << "\tDisplaying list of items, sorted by price:\n";
    for(iter = goodsList.begin(); iter != goodsList.end(); iter++) {
        cout << "\tItem ID: " << iter->goodID << ",";
        cout << "\tName: " << iter->goodName << ",";
        cout << "\tQuantity: " << iter->goodQuantity << ",";
        cout << "\tPrice: $" << iter->goodPrice << ",";
        cout << '\n';
    }
    cout << '\n';
    
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
