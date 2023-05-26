CC=gcc 
CFLAGS=-Wall
BUILD = ./build
FLAGS = -lm -g -Wall 
HEADERS = contactManager.h ui.h contactContainer.h

all: $(BUILD)/main
run: $(BUILD)/main
	$(BUILD)/main

clean:
	rm -r $(BUILD)/*

$(BUILD)/main: $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contactManager.o $(BUILD)/contactContainer.o $(HEADERS)
	$(CC) $(FLAGS) -o $(BUILD)/main $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contactManager.o $(BUILD)/contactContainer.o

$(BUILD)/main.o: main.c $(HEADERS)
	$(CC) $(FLAGS) -c main.c -o $(BUILD)/main.o 

$(BUILD)/ui.o: ui.c $(HEADERS)
	$(CC) $(FLAGS) -c ui.c -o $(BUILD)/ui.o 

$(BUILD)/contactManager.o: contactManager.c $(HEADERS)
	$(CC) $(FLAGS) -c contactManager.c -o $(BUILD)/contactManager.o

$(BUILD)/contactContainer.o: contactContainer.c $(HEADERS)
	$(CC) $(FLAGS) -c contactContainer.c -o $(BUILD)/contactContainer.o
