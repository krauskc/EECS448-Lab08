// Goods.h

#ifndef _GOODS
#define _GOODS

class Goods {
    private:
        
    
    public:
        struct good {
            unsigned    goodID;
            std::string goodName;
            unsigned    goodQuantity;
            double      goodPrice;
        };
        std::list<good> goodsList;
        std::list<good>::iterator iter;
        unsigned goodCount;
        
        Goods();
        //Goods(unsigned ID, std::string name, unsigned quantity, double price);
        unsigned    addGood(unsigned ID, std::string name, unsigned quantity, double price);
        unsigned    removeGood(unsigned ID);
        unsigned    displayList();
        bool        updateGood(unsigned ID, std::string name, unsigned quantity, double price);
        static bool comparePrice(const Goods::good& first, const Goods::good& second);
};

#endif
