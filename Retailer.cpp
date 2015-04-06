#include <iostream>
#include <string>
#include <list>
#include "Goods.h"
#include "Supplier.h"
#include "Retailer.h"

using namespace std;

Retailer::Retailer() {
    theGoods = new Goods;
}

Retailer::Retailer(Goods* goods) {
    theGoods = goods;
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
    
    return 0;
}

unsigned Retailer::acceptOrder(order newOrder) {
    orderList.push_front(newOrder);
    return newOrder.orderID;
}

double Retailer::acceptPayment(unsigned orderID, double amount) {
    for(iter = orderList.begin(); iter != orderList.end(); iter++) {
        if(iter->orderID == orderID) {
            iter->totalPrice -= amount;
            double temp = iter->totalPrice;
            if(iter->totalPrice <= 0.0) {
                orderList.erase(iter);
            }
            return temp;
        }
    }
    
    return -amount;
}

// TODO: orderGoods(), updateGoods()

bool Retailer::ackContact() {
    return true;
}

bool compareOrder(const Retailer::order& first, const Retailer::order& second) {
    return (first.orderID <= second.orderID);
}