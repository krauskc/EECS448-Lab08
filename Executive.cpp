#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

#include "Goods.h"
#include "Supplier.h"
#include "Retailer.h"
#include "Customer.h"
#include "Executive.h"

using namespace std;

void Executive::init() {
    goods = new Goods();
    for(int i = 0; i < 10; i++) {
        string newName = "Good";
        newName += (char)(i + 65);
    	goods->addGood(goods->goodCount, newName, 10*(i + 1), (i + 1)*2.0);
    }
    
    supplier = new Supplier(goods);
    retailer = new Retailer(goods, supplier);
    customer = new Customer(goods);
}

void Executive::loop() {
    string input = "";
    bool running = true;
    while(running) {
        cout << "Customer Menu:\n";
        cout << "1. View Stock\n";
        cout << "2. Start Order\n";
        cout << "3. View Orders\n";
        cout << "...\n";
        cout << "9. Quit\n";
        cout << "\nEnter a number from the list above: ";
        cin >> input;
        switch(input[0]) {
        case '1':
            customer->viewStock();
            break;
        case '2':
            newOrder();
            break;
        case '3':
            retailer->viewOrders();
            break;
        case '9':
        case 'Q':
        case 'q':
            cout << "\nSession terminated";
            running = false;
            break;
        default:
            cout << "Error: Invalid command. Please enter a number from the list.\n\n";
            break;
        }
    }
}

unsigned Executive::newOrder() {
    string input = "";
    unsigned id;
    unsigned qty;
    bool valid = false;
    while(!valid) {
        cout << "\tEnter the Item ID number (or \"cancel\" to return): ";
        input = "";
        cin >> input;
        if(input == "cancel") {
            cout << "\tOrder canceled\n\n";
            return 0;
        } else {
            id = atoi(input.c_str());
        }
        unsigned inStock = retailer->checkSupply(id);
        if(inStock <= 0) {
            cout << "\n\tError: Item not in stock\n";
            valid = false;
            continue;
        } else {
            cout << "\tAmount of " << retailer->getName(id) << " in stock: " << inStock << '\n';
            cout << "\tPrice per unit: $" << retailer->getPrice(id) << '\n';
        }
        bool validQty = false;
        while(!validQty) {
            cout << "\tEnter quantity desired (or \"cancel\" to return): ";
            input = "";
            cin >> input;
            if(input == "cancel") {
                cout << '\n';
                break;
            } else {
                qty = atoi(input.c_str());
            }
            //cout << qty << '\n';
            if(inStock < qty) {
                //cout << "invalid\n";
                cout << "\n\tError: Only " << inStock << " in stock\n";
                validQty = false;
                continue;
            } else {
                //cout << "valid\n";
                validQty = true;
                cout << "\tTotal cost: $" << qty*(retailer->getPrice(id)) << "\n\n";
                break;
            }
        }
        valid = validQty;
    }
    return customer->selectOrder(retailer, retailer->orderCount, id, qty);
}

Executive::Executive() {
    init();
    loop();
}
