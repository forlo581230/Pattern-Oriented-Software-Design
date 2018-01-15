all: hw8 shell

hw8: mainShell.o atom.o list.o struct.o scanner.h parser.h exception.h expression.h
shell: shell.o  atom.o list.o struct.o scanner.h parser.h
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainShell.o atom.o list.o struct.o -lgtest
	g++ -o shell shell.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainShell.o atom.o list.o struct.o -lgtest -lpthread
	g++ -o shell shell.o atom.o list.o struct.o -lgtest -lpthread
endif

# madRace: mainMadRace.o
# 	g++ -o madRace mainMadRace.o -lgtest -lpthread
# mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
# 	g++ -std=c++11 -c mainMadRace.cpp



atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

# hw8: mainShell.o atom.o list.o struct.o scanner.h parser.h exception.h expression.h
# 	g++ -o hw8 mainShell.o atom.o list.o struct.o -lgtest -lpthread
mainShell.o: mainShell.cpp scanner.h  atom.h struct.h variable.h  parser.h exception.h expression.h
	g++ -std=gnu++0x -c mainShell.cpp

# shell: shell.o  atom.o list.o struct.o scanner.h parser.h
# 	g++ -o shell shell.o atom.o list.o struct.o -lgtest -lpthread
shell.o: shell.cpp scanner.h  atom.h struct.h variable.h  parser.h
	g++ -std=gnu++0x -c shell.cpp

#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

# utAtom: mainAtom.o list.o atom.o struct.o
# 	g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
# mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
# 	g++ -std=c++11 -c mainAtom.cpp

# utVariable: mainVariable.o atom.o struct.o
# 		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
# mainVariable.o: mainVariable.cpp utVariable.h variable.h
# 		g++ -std=c++11 -c mainVariable.cpp

# utScanner: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
# 	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread

# mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h exception.h expression.h
# 		g++ -std=c++11 -c mainScanner.cpp

# utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
# 	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread

# mainIterator.o: mainIterator.cpp utIterator.h
# 	g++ -std=c++11 -c mainIterator.cpp





#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp

# clean:
# 	rm -f *.o madRace utAtom utVariable utScanner
# stat:
# 	wc *.h *.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 shell
endif
