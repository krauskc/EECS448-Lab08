// Executive.h

#ifndef _EXECUTIVE
#define _EXECUTIVE

class Executive {
    private:
        
    public:
        Goods*      goods;
        Supplier*   supplier;
        Retailer*   retailer;
        Customer*   customer;
        
        Executive();
        void        init();
        void        loop();
        unsigned    newOrder();
};

#endif
