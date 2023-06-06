CC=gcc 
CFLAGS=-Wall
BUILD = ./build
FLAGS = -lm -g -Wall 
HEADERS = contact.h ui.h contactContainer.h fuzzy_search.h
OBJS = $(BUILD)/contact.o $(BUILD)/contactContainer.o $(BUILD)/ui.o  $(BUILD)/fuzzy_search.o

all: $(BUILD)/main
run: $(BUILD)/main
	$(BUILD)/main

runtest: $(BUILD)/test
	$(BUILD)/test
	
valgrindtest:$(BUILD)/test
	valgrind $(BUILD)/test

valgrindmain:$(BUILD)/main
	valgrind $(BUILD)/main
clean:
	rm -r $(BUILD)/*
cleanContacts:
	rm -r ./.contacts.txt

$(BUILD)/main: $(BUILD)/main.o $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) -o $(BUILD)/main  $(BUILD)/main.o $(OBJS)

$(BUILD)/test: $(BUILD)/test.o $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) -o $(BUILD)/test $(BUILD)/test.o $(OBJS)


$(BUILD)/%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@