
all: flex gcc
	@echo "Done."

flex: scanner.l
	flex scanner.l

gcc: scanner.c
	gcc -Wall -o scanner scanner.c

clean:
	@rm -f scanner.c scanner
