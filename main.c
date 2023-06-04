#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "contact.h"
#include "contactContainer.h"

const char *menu_items[] = {
    "Quit",
    "Add a new contact",
    "List all contacts",
    "Search for contact",
    "Delete a contact"};

#define QUIT 0
#define ADD_NEW_CONTACT 1
#define LIST_ALL_CONTACTS 2
#define SEARCH_FOR_CONTACT 3
#define DELTE_A_CONTACT 4

void main_menu(ContactContainer *container);

void add_new_contact(ContactContainer *container);

void list_all_contacts(ContactContainer *container);

int main()
{
    size_t container_intial_capacity = 10;
    ContactContainer *container = contactContainer_create(container_intial_capacity);
    main_menu(container);
    contactContianer_destroy(container);
    return 0;
}

void main_menu(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(menu_items, sizeof(menu_items) / sizeof(const char *));
    while (1)
    {

        print_title_banner();
        int choice = get_choice(&menu);
        clear_console();
        switch (choice)
        {

        case MULTIPLE_CHOICE_MENU_INVALID_CHOICE:
            printf("Your choice was invalid please select another option\n");
            break;
        case QUIT:
            return;
            break;
        case ADD_NEW_CONTACT:
            add_new_contact(container);
            break;
        case LIST_ALL_CONTACTS:
            list_all_contacts(container);
        }
        clear_console();
    }
}

void add_new_contact(ContactContainer *container)
{

    bool running = true;
    while (running)
    {
        clear_console();
        bool error = true;
        Contact new_contact = get_contact_from_ui(&error);
        if (error)
        {
            running = yes_no_query("The contact you entered is invalid, Would you like to enter again");
            clear_console();
            continue;
        }
        clear_console();
        if (contactContianer_search_contact_by_name(container, new_contact.name) != CONTACT_DOES_NOT_EXIST)
        {
            running = yes_no_query("A contact by the given name already exist,Would you like to enter again");
            clear_console();
            continue;
        }
        contactContianer_push_contact(container, &new_contact);
        press_any_key_to_continue("The contact was added sucessfully");
        break;
    }
}

void list_all_contacts(ContactContainer *container)
{
    if (contactContaier_get_size(container) == 0)
    {
        printf("There are no contacts\n");
    }
    else
    {
        contactContainer_for_all_contacts_do(container, debug_print_contact);
    }
    press_any_key_to_continue("");
}