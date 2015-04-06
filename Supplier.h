// Supplier.h

#ifndef _SUPPLIER
#define _SUPPLIER

class Supplier {
    private:
        
    public:
        unsigned    supplierID;
        std::string supplierName;
        Goods*      theGoods;
        
        Supplier();
        Supplier(Goods* goods);
        int         addGood(unsigned ID, std::string name, unsigned quantity, double price);
        int         removeGood(unsigned ID);
        bool        updateGood(unsigned ID, std::string name, unsigned quantity, double price);
        double      acceptPayment(double amount);
};

#endif