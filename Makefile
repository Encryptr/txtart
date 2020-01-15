CC = gcc
CFLAGS = -Wall -std=c99 
FILE = demo/txtart_demo.c
EXE = txtart

all: compile

compile:
	$(CC) $(CFLAGS) $(FILE) -o $(EXE)

clean: 
	rm $(EXE)