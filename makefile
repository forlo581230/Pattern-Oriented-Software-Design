all: hw7

hw7: mainIterator.o struct.o term.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainIterator.o struct.o term.o list.o -lgtest
else
	g++ -o hw7 mainIterator.o struct.o term.o list.o -lgtest -lpthread
endif

struct.o: struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

list.o: list.cpp list.h
		g++ -std=gnu++0x -c list.cpp

# iterator.o: iterator.cpp iterator.h
# 		g++ -std=gnu++14 -c iterator.cpp

term.o: term.cpp term.h
		g++ -std=gnu++0x -c term.cpp

mainIterator.o: mainIterator.cpp utIterator.h atom.h number.h variable.h list.h scanner.h parser.h node.h iterator.h term.h struct.h
		g++ -std=gnu++0x -c mainIterator.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif

