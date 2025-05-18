CC=gcc

all: clearTerminal convertSymbol run

convertSymbol: convertSymbol.c
	$(CC) -Wall convertSymbol.c -o convertSymbol

clearTerminal: 
	clear

clean: 
	rm -f convertSymbol

run:
	./convertSymbol

.PHONY: clearTerminal clean