#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "contact.h"
#include "contactContainer.h"

const char *STORAGE_FILE = ".contacts.txt";
const char *menu_items[] = {
    "Quit",
    "Add a new contact",
    "List all contacts",
    "Search for contact",
    "Delete a contact"};

enum MainMenuItems
{
    QUIT = 0,
    ADD_NEW_CONTACT = 1,
    LIST_ALL_CONTACTS = 2,
    SEARCH_FOR_CONTACT = 3,
    DELTE_A_CONTACT = 4,
};
const char *search_menu_items[] = {
    "Search by Name",
    "Search by Number",
    "Go back to main menu",
};

enum SearhMenuItems
{
    SEARCH_BY_NAME = 0,
    SEARCH_BY_NUMBER = 1,
    GO_BACK_TO_MAIN_MENU = 2,
};

void main_menu(ContactContainer *container);

void add_new_contact(ContactContainer *container);

void list_all_contacts(ContactContainer *container);
void search_for_contact(ContactContainer *container);
Contact *search_for_contact_by_name(ContactContainer *container);

Contact *search_for_contact_by_number(ContactContainer *container);

void delete_contact(ContactContainer *container);

int main()
{
    size_t container_intial_capacity = 10;
    ContactContainer *container = contactContainer_create(container_intial_capacity);

    FILE *fptr = fopen(STORAGE_FILE, "r");
    if (fptr != NULL)
    {
        load_from_file(container, fptr);
        fclose(fptr);
    }
    main_menu(container);
    FILE *new_fptr = fopen(STORAGE_FILE, "w+");
    save_to_file(container, new_fptr);
    contactContianer_destroy(container);
    fclose(new_fptr);
    return 0;
}

void main_menu(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(menu_items, sizeof(menu_items) / sizeof(const char *));
    bool running = true;
    while (running)
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
            running = false;
            break;
        case ADD_NEW_CONTACT:
            add_new_contact(container);
            break;
        case LIST_ALL_CONTACTS:
            list_all_contacts(container);
            break;
        case SEARCH_FOR_CONTACT:
            search_for_contact(container);
            break;
        case DELTE_A_CONTACT:
            delete_contact(container);
            break;
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

void delete_contact(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(search_menu_items, 3);
    printf("What method would you like to search for the contact to be deleted?\n");
    bool running = true;
    Contact *contact_to_be_deleted = INVALID_CONTACT;
    while (running)
    {

        int choice = get_choice(&menu);
        switch (choice)
        {
        case MULTIPLE_CHOICE_MENU_INVALID_CHOICE:
            press_any_key_to_continue("Your choice was invalid please select another option");
            clear_console();
            continue;
            break;
        case SEARCH_BY_NAME:
            contact_to_be_deleted = search_for_contact_by_name(container);
            break;
        case SEARCH_BY_NUMBER:
            contact_to_be_deleted = search_for_contact_by_number(container);
            break;
        case GO_BACK_TO_MAIN_MENU:
            break;
        }

        if (contact_to_be_deleted == INVALID_CONTACT)
        {
            break;
        }
        printf("The following contact will be deleted\n");
        print_contact(contact_to_be_deleted);
        bool delete_confirmed = yes_no_query("Are you sure sure you want to delet this contact?");
        if (!delete_confirmed)
        {
            press_any_key_to_continue("Deletion aborted");
            break;
        }

        contactContainer_delete_contact(container, contact_to_be_deleted);
        press_any_key_to_continue("The contact has been delted");
        break;
    }
    clear_console();
}
void search_for_contact(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(search_menu_items, 3);
    bool running = true;
    while (running)
    {

        int choice = get_choice(&menu);
        switch (choice)
        {
        case MULTIPLE_CHOICE_MENU_INVALID_CHOICE:
            press_any_key_to_continue("Your choice was invalid please select another option");
            clear_console();
            continue;
            break;
        case SEARCH_BY_NAME:
            search_for_contact_by_name(container);
            break;
        case SEARCH_BY_NUMBER:
            search_for_contact_by_number(container);
            break;
        case GO_BACK_TO_MAIN_MENU:
            break;
        }
        running = false;
        break;
    }
    clear_console();
}

Contact *search_for_contact_by_name(ContactContainer *container)
{

    clear_console();
    char buffer[MAX_NAME_LENGTH + 5] = {0};
    bool running = true;
    Contact *searched_contact = INVALID_CONTACT;
    while (running)
    {
        clear_console();
        bool error = true;
        error = get_name(buffer);
        if (error)
        {
            bool try_again = yes_no_query("The entered name has invalid format would you like to enter again?");
            if (try_again)
            {
                continue;
            }
            break;
        }

        searched_contact = contactContianer_search_contact_by_name(container, buffer);
        if (searched_contact == INVALID_CONTACT)
        {
            bool try_again = yes_no_query("There are no contacts saved that match the name you entered.would you like to try again?");
            if (try_again)
            {
                continue;
            }
            break;
        }

        printf("A contact with the given name was found!\n");
        print_contact(searched_contact);
        bool try_again = yes_no_query("Would you like to keep searching?");
        if (try_again)
        {
            continue;
        }
        break;
    }
    clear_console();
    return searched_contact;
}

Contact *search_for_contact_by_number(ContactContainer *container)
{
    clear_console();
    char buffer[PHONE_NUMBER_LENGTH + 5] = {0};
    bool running = true;
    Contact *searched_contact = INVALID_CONTACT;
    while (running)
    {
        clear_console();
        bool error = true;
        error = get_phone_number_from_ui(buffer);
        if (error)
        {
            bool try_again = yes_no_query("The entered number has invalid format would you like to enter again?");
            if (try_again)
            {
                continue;
            }
            break;
        }

        searched_contact = contactContianer_search_contact_by_number(container, buffer);
        if (searched_contact == INVALID_CONTACT)
        {
            bool try_again = yes_no_query("There are no contacts saved that match the number you entered.would you like to try again?");
            if (try_again)
            {
                continue;
            }
            break;
        }

        printf("A contact with the given number was found!\n");
        print_contact(searched_contact);
        bool try_again = yes_no_query("Would you like to keep searching?");
        if (try_again)
        {
            continue;
        }
        break;
    }
    clear_console();
    return searched_contact;
}