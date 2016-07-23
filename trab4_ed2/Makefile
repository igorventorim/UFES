all:
	gcc -o gera gerador.c -Wall -Wextra -Wconversion
	gcc -o trab4 trab4.c io.c ordenacao.c fila.c -Wall -Wextra -Wconversion
	pdflatex trab4
	bibtex trab4
	pdflatex trab4
	pdflatex trab4

clean:
	rm -f gera
	rm -f trab4
	rm -f amostra.txt
	rm trab4.pdf trab4.brf trab4.blg trab4.bbl trab4.out trab4.aux trab4.idx trab4.log

debug:
	gcc -o gera gerador.c -Wall -Wconversion -Wextra -g
	gcc -o trab4 trab4.c io.c ordenacao.c fila.c -Wall -Wextra -Wconversion -g

