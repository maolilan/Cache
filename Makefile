all: Cache

Cache: main.o utility.o LFUcache.o LRUcache.o
	g++ main.o utility.o LFUcache.o LRUcache.o -o Cache

main.o: main.cpp
	g++ -c -std=c++0x main.cpp

utility.o: utility.cpp
	g++ -c -std=c++0x utility.cpp

LFUcache.o: LFUcache.cpp
	g++ -c -std=c++0x LFUcache.cpp

LRUcache.o: LRUcache.cpp
	g++ -c -std=c++0x LRUcache.cpp

clean:
	rm -rf *o Cache
