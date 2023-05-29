#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "contact.h"

#define MULTIPLE_CHOICE_MENU_INVALID_CHOICE -1
void print_title_banner();
void clear_console();
long long get_int(const char *message, bool *error);

typedef struct
{
    const char **menu_items;
    int size;
} MultipltChoiceMenu;

MultipltChoiceMenu create_multiple_choice_menu(const char **menu_items, int number_of_items);
int get_choice(MultipltChoiceMenu *menu);
Contact get_contact_from_ui(bool *error);
