#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "contactManager.h"

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
        if (choice == 0)
        {
            break;
        }
        if (choice == 1)
        {
            clear_console();
            bool error = true;
            // contact new_contact;
            contact new_contact = get_contact_from_ui(&error);
            if (error)
            {
                clear_console();
                printf("The contact you entered is invalid\n");
                continue;
            }
            clear_console();
            // printf("%d\n", sizeof(new_contact.name));
            debug_print_contact(&new_contact);
        }
    }
}