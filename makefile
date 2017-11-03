all: hw5

hw5: mainParser.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o -lgtest
else
	g++ -o hw5 mainParser.o -lgtest -lpthread
endif

mainParser.o: mainParser.cpp utParser.h atom.h number.h variable.h struct.h list.h scanner.h parser.h
		g++ -std=gnu++0x -c mainParser.cpp		

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
