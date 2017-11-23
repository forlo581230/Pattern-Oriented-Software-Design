all: hw6

hw6: mainParser.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainParser.o -lgtest
else
	g++ -o hw6 mainParser.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp utParser.h atom.h number.h variable.h struct.h list.h scanner.h parser.h node.h
		g++ -std=gnu++0x -c mainParser.cpp		

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
