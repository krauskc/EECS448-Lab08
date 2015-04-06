// Customer.h

#ifndef _CUSTOMER
#define _CUSTOMER

class Customer {
    private:
        
    public:
        unsigned    customerID;
        std::string customerName;
        std::string paymentMethod;
        Goods*      theGoods;
        
        Customer();
        Customer(Goods* goods);
        int         viewStock();
        // selectOrder() is really createOrder()
        unsigned    selectOrder(Retailer* retailer, unsigned orderID, unsigned goodID, unsigned qty);
        unsigned    viewOrder(Retailer* retailer, unsigned ID);
        double      makePayment(Retailer* retailer, unsigned orderID, double amount);
        bool        contactRetailer();
};

#endif