CC=gcc

all: clearTerminal convertSymbol

convertSymbol: convertSymbol.c
	$(CC) -Wall convertSymbol.c -o convertSymbol

clearTerminal: 
	clear

clean: 
	rm -f convertSymbol

.PHONY: clearTerminal clean