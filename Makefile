CC=gcc 
CFLAGS=-Wall
BUILD = ./build
FLAGS = -lm -g -Wall 

all: $(BUILD)/main
run: $(BUILD)/main
	$(BUILD)/main

clean:
	rm -r $(BUILD)/*
$(BUILD)/main: $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contactManager.o
	$(CC) $(FLAGS) -o $(BUILD)/main $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contactManager.o

$(BUILD)/main.o: main.c
	$(CC) $(FLAGS) -c main.c -o $(BUILD)/main.o 

$(BUILD)/ui.o: ui.c
	$(CC) $(FLAGS) -c ui.c -o $(BUILD)/ui.o 

$(BUILD)/contactManager.o: contactManager.c
	$(CC) $(FLAGS) -c contactManager.c -o $(BUILD)/contactManager.o