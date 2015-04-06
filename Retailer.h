// Retailer.h

#ifndef _RETAILER
#define _RETAILER

class Retailer {
    private:
        
    
    public:
        struct order {
            unsigned    orderID;
            Goods::good theGood;
            unsigned    orderQty;
            double      totalPrice;
        };
        std::list<order> orderList;
        std::list<order>::iterator iter;
        std::string retailerName;
        Goods* theGoods;
        Supplier* SupplierA;
        
        Retailer();
        Retailer(Goods* goods, Supplier* supplier);
        double      getOrder(unsigned orderID);
        unsigned    checkSupply(unsigned goodID);
        unsigned    acceptOrder(order newOrder);
        double      acceptPayment(unsigned orderID, double amount);
        bool        orderGoods(Supplier* supplier, unsigned goodID, unsigned quantity);
        bool        updateGoods(unsigned ID, std::string name, unsigned quantity, double price);
        bool        ackContact();
        static bool compareOrder(order first, order second);
};

#endif
