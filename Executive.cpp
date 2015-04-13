#include <cstdlib>
#include <iostream>
#include <cstdio>
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
        cout << "4. Make Payment\n";
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
        case '4':
            payment();
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
        if(input == "cancel" || input == "Cancel" || input == "CANCEL") {
            cout << "\tOrder canceled\n\n";
            return 0;
        } else if(isNumber(input)) {
            id = atoi(input.c_str());
        } else {
            cout << "\tError: Not a valid number\n";
            valid = false;
            continue;
        }
        unsigned inStock = retailer->checkSupply(id);
        if(inStock <= 0) {
            cout << "\n\tError: Item not in stock\n";
            valid = false;
            continue;
        } else {
            cout << "\tAmount of " << retailer->getName(id) << " in stock: " << inStock << '\n';
            printf("\tPrice per unit: $%.2f\n", retailer->getPrice(id));
        }
        bool validQty = false;
        while(!validQty) {
            cout << "\tEnter quantity desired (or \"cancel\" to return): ";
            input = "";
            cin >> input;
            if(input == "cancel" || input == "Cancel" || input == "CANCEL") {
                cout << '\n';
                break;
            } else if(isNumber(input)) {
                qty = atoi(input.c_str());
            } else {
                cout << "\tError: Not a valid number\n";
                validQty = false;
                continue;
            }
            //cout << qty << '\n';
            if(inStock < qty) {
                //cout << "invalid\n";
                cout << "\n\tOnly " << inStock << " in stock. Order more from supplier? (Y/N): ";
                input = "";
                cin >> input;
                if(input[0] == 'Y' || input[0] == 'y') {
                    retailer->orderGoods(supplier, id, (qty - inStock));
                    cout << '\t' << (qty - inStock) << " additional units ordered\n";
                    validQty = true;
                    printf("\tTotal Due: $%.2f\n", qty*(retailer->getPrice(id)));
                    break;
                } else {
                    validQty = false;
                    continue;
                }
            } else {
                //cout << "valid\n";
                validQty = true;
                printf("\tTotal Due: $%.2f\n", qty*(retailer->getPrice(id)));
                break;
            }
        }
        if(validQty) {
            cout << "\tConfirm? (Y/N): ";
            input = "";
            cin >> input;
            cout << '\n';
            valid = (input[0] == 'Y' || input[0] == 'y');
        } else {
            valid = false;
        }
    }
    printf("\tOrder added. Amount due: $%.2f\n\n", qty*retailer->getPrice(id));
    return customer->selectOrder(retailer, retailer->orderCount, id, qty);
}

void Executive::payment() {
    string input = "";
    unsigned orderID;
    double amount, amountDue;
    bool valid = false;
    while(!valid) {
        cout << "\tEnter the Order ID number (or \"cancel\" to return): ";
        input = "";
        cin >> input;
        if(input == "cancel" || input == "Cancel" || input == "CANCEL") {
            cout << "\tPayment canceled\n\n";
            return;
        } else if(isNumber(input)) {
            orderID = atoi(input.c_str());
        } else {
            cout << "\tError: Not a valid number\n";
            valid = false;
            continue;
        }
        amountDue = retailer->getOrder(orderID);
        if(amountDue <= 0) {
            cout << "\n\tError: Order not active\n";
            valid = false;
            continue;
        } else {
            cout << "\tOrder #" << orderID << '\n';
            printf("\tAmount Due: $%.2f\n", retailer->getOrder(orderID));
        }
        bool validAmount = false;
        while(!validAmount) {
            cout << "\tEnter payment amount (or \"cancel\" to return): ";
            input = "";
            cin >> input;
            if(input == "cancel" || input == "Cancel" || input == "CANCEL") {
                cout << '\n';
                break;
            } else if(isNumber(input)) {
                amount = atof(input.c_str());
                validAmount = true;
            } else {
                cout << "\tError: Not a valid number\n";
                validAmount = false;
                continue;
            }
            printf("\n\tPayment of $%.2f\n", amount);
            if(amountDue < amount) {
                printf("\tChange: $%.2f\n", (amount - amountDue));
            } else {
                printf("\tRemaining amount due: $%.2f\n", (amountDue - amount));
            }
        }
        if(validAmount) {
            cout << "\tConfirm? (Y/N): ";
            input = "";
            cin >> input;
            cout << '\n';
            valid = (input[0] == 'Y' || input[0] == 'y');
        } else {
            valid = false;
        }
    }
    if(amountDue >= amount) {
        printf("\tPayment of $%.2f complete. Remaining balance: $%.2f\n\n", amount, (amountDue - amount));
    } else {
        printf("\tPayment of $%.2f complete. Change: $%.2f\n\n", amount, (amount - amountDue));
    }
    customer->makePayment(retailer, orderID, amount);
}

bool Executive::isNumber(const string str) {
    for(unsigned i = 0; i < str.length(); i++) {
        if(!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

Executive::Executive() {
    init();
    loop();
}
