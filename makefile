lab8: main.o
	g++ -g -o lab8 main.o

main.o: main.cpp Executive.cpp Customer.h Customer.cpp Goods.h Goods.cpp Retailer.h Retailer.cpp Supplier.h Supplier.cpp
	g++ -c -std=c++11 -g main.cpp

clean:
	rm lab8 *.o
