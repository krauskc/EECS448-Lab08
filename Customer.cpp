#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include "Goods.h"
#include "Supplier.h"
#include "Retailer.h"
#include "Customer.h"

using namespace std;

Customer::Customer() {
    theGoods = new Goods();
}

Customer::Customer(Goods* goods) {
    theGoods = goods;
}

int Customer::viewStock() {
    return theGoods->displayList();
}

unsigned Customer::selectOrder(Retailer* retailer, unsigned orderID, unsigned goodID, unsigned qty) {
    Retailer::order *newOrder = new Retailer::order();
    newOrder->orderID = orderID;
    newOrder->orderQty = qty;
    for(theGoods->iter = theGoods->goodsList.begin(); theGoods->iter != theGoods->goodsList.end(); theGoods->iter++) {
        if(theGoods->iter->goodID == goodID) {
            newOrder->theGood = *theGoods->iter;
            newOrder->totalPrice = newOrder->theGood.goodPrice*qty;
            break;
        }
    }
    retailer->acceptOrder(*newOrder);
    
    return newOrder->orderID;
}

unsigned Customer::viewOrder(Retailer* retailer, unsigned ID) {
    unsigned orderID = 0;
    for(retailer->iter = retailer->orderList.begin(); retailer->iter != retailer->orderList.end(); retailer->iter++) {
        if(retailer->iter->orderID == ID) {
            cout << "Order# " << ID << '\n';
            cout << "Good: " << retailer->iter->theGood.goodName << '\n';
            cout << "Quantity: " << retailer->iter->orderQty << '\n';
            printf("Amount Due: $%.2f\n", retailer->iter->totalPrice);
            orderID = ID;
            break;
        }
    }
    if(!orderID) {
        cout << "Order not found\n";
    }
    
    return orderID;
}

double Customer::makePayment(Retailer* retailer, unsigned orderID, double amount) {
    return retailer->acceptPayment(orderID, amount);
}

bool Customer::contactRetailer(Retailer* retailer) {
    if(retailer != NULL) {
        return retailer->ackContact();
    } else {
        return false;
    }
}
