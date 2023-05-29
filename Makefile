CC=gcc 
CFLAGS=-Wall
BUILD = ./build
FLAGS = -lm -g -Wall 
HEADERS = contact.h ui.h contactContainer.h

all: $(BUILD)/main
run: $(BUILD)/main
	$(BUILD)/main

runtest: $(BUILD)/test
	$(BUILD)/test
	
valgrindtest:$(BUILD)/test
	valgrind $(BUILD)/test
clean:
	rm -r $(BUILD)/*

$(BUILD)/main: $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contact.o $(BUILD)/contactContainer.o $(HEADERS)
	$(CC) $(FLAGS) -o $(BUILD)/main $(BUILD)/main.o $(BUILD)/ui.o $(BUILD)/contact.o $(BUILD)/contactContainer.o

$(BUILD)/test: $(BUILD)/test.o $(BUILD)/ui.o $(BUILD)/contact.o $(BUILD)/contactContainer.o $(HEADERS)
	$(CC) $(FLAGS) -o $(BUILD)/test $(BUILD)/test.o $(BUILD)/ui.o $(BUILD)/contact.o $(BUILD)/contactContainer.o

$(BUILD)/main.o: main.c $(HEADERS)
	$(CC) $(FLAGS) -c main.c -o $(BUILD)/main.o 

$(BUILD)/ui.o: ui.c $(HEADERS)
	$(CC) $(FLAGS) -c ui.c -o $(BUILD)/ui.o 

$(BUILD)/contact.o: contact.c $(HEADERS)
	$(CC) $(FLAGS) -c contact.c -o $(BUILD)/contact.o

$(BUILD)/contactContainer.o: contactContainer.c $(HEADERS)
	$(CC) $(FLAGS) -c contactContainer.c -o $(BUILD)/contactContainer.o

$(BUILD)/test.o: test.c $(HEADERS)
	$(CC) $(FLAGS) -c test.c -o $(BUILD)/test.o 