

all: TableS7S9.o Misty1.o CryptageMessage.o IhmConsole.o IhmConsole

IhmConsole: bin/IhmConsole.o bin/CryptageMessage.o bin/Misty1.o
	g++ -o IhmConsole bin/IhmConsole.o bin/CryptageMessage.o bin/Misty1.o

IhmConsole.o: src/IhmConsole.cpp src/CryptageMessage.hpp
	g++ -Wall -c src/IhmConsole.cpp; mv IhmConsole.o bin/

CryptageMessage.o: src/CryptageMessage.cpp src/CryptageMessage.hpp src/Misty1.hpp
	g++ -Wall -c src/CryptageMessage.cpp; mv CryptageMessage.o bin/

Misty1.o: src/Misty1.cpp src/TableS7S9.cpp src/Misty1.hpp
	g++ -Wall -std=c++0x -c src/Misty1.cpp; mv Misty1.o bin/

TableS7S9.o: src/TableS7S9.cpp
	g++ -Wall -std=c++0x -c src/TableS7S9.cpp; mv TableS7S9.o bin/

clean: 
	rm -f *~ *.o bin/*.o IhmConsole
