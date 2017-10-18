all: utVariable utStruct

utVariable: mainVariable.o
ifeq (${OS}, Windows_NT)
	g++ -o utVariable mainVariable.o  -lgtest
else
	g++ -o utVariable mainVariable.o  -lgtest -lpthread
endif
		
mainVariable.o: mainVariable.cpp utVariable.h atom.h number.h variable.h struct.h
		g++ -std=c++11 -c mainVariable.cpp

utStruct: mainStruct.o
ifeq (${OS}, Windows_NT)
	g++ -o utStruct mainStruct.o -lgtest
else
	g++ -o utStruct mainStruct.o -lgtest -lpthread
endif
		
mainStruct.o: mainStruct.cpp utStruct.h struct.h atom.h number.h variable.h
		g++ -std=c++11 -c mainStruct.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
