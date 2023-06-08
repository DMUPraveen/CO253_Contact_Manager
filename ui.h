#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "contact.h"

#define MULTIPLE_CHOICE_MENU_INVALID_CHOICE -1
void print_title_banner();
void clear_console();
void press_any_key_to_continue(const char *msg);
bool yes_no_query(const char *query);
long long get_int(const char *message, bool *error);

typedef struct
{
    const char **menu_items;
    int size;
} MultipltChoiceMenu;

MultipltChoiceMenu create_multiple_choice_menu(const char **menu_items, int number_of_items);
int get_choice(MultipltChoiceMenu *menu);
Contact get_contact_from_ui(bool *error);

bool get_name(char *name_buffer);

bool get_phone_number_from_ui(char *phone_number);

void print_contact(const Contact *contact);

bool get_line_from_input(char *buffer, int max_number, const char *message);

void table_row_print(const Contact *contact);

void table_header_print();

void print_table_seperator();

Contact edit_contact_from_ui(Contact *contact, bool *error);