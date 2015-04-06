#include <string>
#include <list>
#include "Goods.h"
#include "Supplier.h"

using namespace std;

Supplier::Supplier() {
    theGoods = new Goods();
}

Supplier::Supplier(Goods* goods) {
    theGoods = goods;
}

int Supplier::addGood(unsigned ID, string name, unsigned quantity, double price) {
    return theGoods->addGood(ID, name, quantity, price);
}

int Supplier::removeGood(unsigned ID) {
    return theGoods->removeGood(ID);
}

bool Supplier::updateGood(unsigned ID, string name, unsigned quantity, double price) {
    return theGoods->updateGood(ID, name, quantity, price);
}

double Supplier::acceptPayment(double amount) {
    return amount;
}