#Name:Beiming CUI
#Loginid:beimingc@usc.edu
#EE599
#Spring 2017

mytest: mytest.o hash_set.o
	g++ -ggdb -Wall -pthread -std=c++11 -o mytest mytest.o hash_set.o

mytest.o: mytest.cpp hashset.hpp
	g++ -ggdb -Wall -pthread -Wno-sign-compare -std=c++11 -c mytest.cpp

hash_set.o: hash_set.cpp hashset.hpp
	g++ -ggdb -Wall -pthread -Wno-sign-compare -std=c++11 -c hash_set.cpp 

clean:
	rm mytest.o hash_set.o mytest



