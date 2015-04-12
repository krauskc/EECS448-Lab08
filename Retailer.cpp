#include <iostream>
#include <string>
#include <list>
#include "Goods.h"
#include "Supplier.h"
#include "Retailer.h"

using namespace std;

Retailer::Retailer() {
    theGoods = new Goods;
    SupplierA = new Supplier;
    orderCount = 0;
}

Retailer::Retailer(Goods* goods, Supplier* supplier) {
    theGoods = goods;
    SupplierA = supplier;
    orderCount = 0;
}

double Retailer::getOrder(unsigned orderID) {
    for(iter = orderList.begin(); iter != orderList.end(); iter++) {
        if(iter->orderID == orderID) {
            return iter->totalPrice;
        }
    }
    
    return -1.0;
}

unsigned Retailer::checkSupply(unsigned goodID) {
    for(theGoods->iter = theGoods->goodsList.begin(); theGoods->iter != theGoods->goodsList.end(); theGoods->iter++) {
        if(theGoods->iter->goodID == goodID) {
            return theGoods->iter->goodQuantity;
        }
    }
    
    return -1;
}

string Retailer::getName(unsigned goodID) {
    for(theGoods->iter = theGoods->goodsList.begin(); theGoods->iter != theGoods->goodsList.end(); theGoods->iter++) {
        if(theGoods->iter->goodID == goodID) {
            return theGoods->iter->goodName;
        }
    }

    return "Not found";
}

double Retailer::getPrice(unsigned goodID) {
    for(theGoods->iter = theGoods->goodsList.begin(); theGoods->iter != theGoods->goodsList.end(); theGoods->iter++) {
        if(theGoods->iter->goodID == goodID) {
            return theGoods->iter->goodPrice;
        }
    }

    return -1.0;
}

unsigned Retailer::acceptOrder(order newOrder) {
    orderList.push_front(newOrder);
    if(checkSupply(newOrder.theGood.goodID) > newOrder.orderQty) {
        
    } else {
        
    }
    
    orderCount++;
    return newOrder.orderID;
}

double Retailer::acceptPayment(unsigned orderID, double amount) {
    for(iter = orderList.begin(); iter != orderList.end(); iter++) {
        if(iter->orderID == orderID) {
            iter->totalPrice -= amount;
            double temp = iter->totalPrice;
            if(iter->totalPrice <= 0.0) {
                orderList.erase(iter);
                if(checkSupply(iter->theGood.goodID) < iter->orderQty) {
                    orderGoods(SupplierA, iter->theGood.goodID, iter->orderQty);
                }
                updateGoods(iter->theGood.goodID, iter->theGood.goodName, iter->theGood.goodQuantity - iter->orderQty, iter->theGood.goodPrice);
            }
            return temp;
        }
    }
    
    return -amount;
}

bool Retailer::orderGoods(Supplier* supplier, unsigned goodID, unsigned quantity) {
    for(theGoods->iter = theGoods->goodsList.begin(); theGoods->iter != theGoods->goodsList.end(); theGoods->iter++) {
        if(theGoods->iter->goodID == goodID) {
            return supplier->updateGood(goodID, theGoods->iter->goodName, quantity, theGoods->iter->goodPrice);
        }
    }
    return false;
}

bool Retailer::updateGoods(unsigned ID, std::string name, unsigned quantity, double price) {
    return theGoods->updateGood(ID, name, quantity, price);
}

bool Retailer::ackContact() {
    return true;
}

void Retailer::viewOrders() {
    orderList.sort(compareOrder);
    bool ordersExist = false;
    for(iter = orderList.begin(); iter != orderList.end(); iter++) {
        if(!ordersExist) {
            ordersExist = true;
            cout << "\tDisplaying list of orders, sorted by ID:\n";
        }
        cout << "\tOrder ID: " << iter->orderID << ",";
        cout << "\tItem Name: " << iter->theGood.goodName << ",";
        cout << "\tQuantity: " << iter->orderQty << ",";
        cout << "\tTotal Price: $" << iter->totalPrice << ",";
        cout << '\n';
    }
    if(!ordersExist) {
        cout << "\tNo orders exist\n";
    }
    cout << '\n';
}

bool Retailer::compareOrder(const Retailer::order& first, const Retailer::order& second) {
    return (first.orderID <= second.orderID);
}
