
all: flex gcc
	@echo "Done."

flex: scanner.l
	flex scanner.l

gcc: scanner.c
	gcc -Wall -o trab1 scanner.c

clean:
	@rm -f scanner.c trab1
