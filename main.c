#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

const char *menu_items[] = {
    "Quit",
    "Add a new contact"
    "List all contacts",
    "Search for contact",
    "Delete a contact"};
int main()
{
    clear_console();
    print_title_banner();
    MultipltChoiceMenu menu = create_multiple_choice_menu(menu_items, sizeof(menu_items) / sizeof(const char *));
    while (1)
    {
        int choice = get_choice(&menu);
        clear_console();
        if (choice == MULTIPLE_CHOICE_MENU_INVALID_CHOICE)
        {
            printf("Your choice was invalid please select another option\n");
            continue;
        }
        printf("Your choice was %d\n", choice);
        if (choice == 0)
        {
            break;
        }
    }
}