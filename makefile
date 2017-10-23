all: hw4

hw4: mainList.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainList.o -lgtest
else
	g++ -o hw4 mainList.o -lgtest -lpthread
endif

mainList.o: mainList.cpp utList.h list.h struct.h atom.h number.h variable.h utVariable.h utStruct.h
		g++ -std=gnu++0x -c mainList.cpp		


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
