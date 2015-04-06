#include <iostream>
#include <string>
#include <list>

#include "Goods.h"
#include "Supplier.h"
#include "Retailer.h"
#include "Customer.h"

using namespace std;

unsigned goodCount = 0;
Goods* goods;

void addGood(string name, unsigned quantity, double price) {
    goods->addGood(goodCount, name, quantity, price);
    goodCount++;
}

void init() {
    goods = new Goods();
    for(int i = 0; i < 10; i++) {
        addGood("Good" + (char)(i + 65), 10*i, i*2.0);
    }
    
    //TODO: Finish init and rest of Executive, then Main
}

int Executive() {
    init();
    
    return 0;
}
