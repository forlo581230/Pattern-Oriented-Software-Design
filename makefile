all: hw3

hw3: mainStruct.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainStruct.o -lgtest
else
	g++ -o hw3 mainStruct.o -lgtest -lpthread
endif

mainStruct.o: mainStruct.cpp utStruct.h utVariable.h struct.h atom.h number.h variable.h
		g++ -std=gnu++0x -c mainStruct.cpp		
#mainVariable.o: mainVariable.cpp utVariable.h atom.h number.h variable.h struct.h
#		g++ -std=c++11 -c mainVariable.cpp



clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
