
main.exe: main.o
	g++ $(MODE)-std=c++0x main.o -o main.exe

# Per il codice templato e' importante mettere i file .h
# tra le dipendenze per far rilevare a make le modifiche
# al codice della classe
main.o: main.cpp Graph.hpp
	g++ $(MODE)-std=c++0x -c main.cpp -o main.o

.PHONY: clean

clean:
	rm *.exe *.o
