.PHONEY: build clean

build:minimax

minimax:help.c
	gcc -Wall -g help.c -o minimax

clean:
	rm -rf minimax
