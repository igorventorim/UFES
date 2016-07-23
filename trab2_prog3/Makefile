CC=g++ -std=c++11
FLAGS= $(WARN) -O2 $G
WARN= -Wall -Wextra
SOURCES= Main.cpp Midia.cpp Filme.cpp Livro.cpp Serie.cpp Emprestimo.cpp Genero.cpp FileIO.cpp Pessoa.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=trab2

all:
	$(CC) -o $(EXEC) $(SOURCES) #$(FLAGS) 
	
run:
	./trab2 -g generos.csv -p pessoas.csv -m midias.csv -e emprestimos.csv

clean:
	rm -f $(EXEC)
	rm -f 1-estatisticas.txt 2-porpessoa.csv 3-emprestimos.csv 4-wishlist.csv

debug:
	$(CC) -o $(EXEC) $(SOURCES) $(FLAGS) -g	
