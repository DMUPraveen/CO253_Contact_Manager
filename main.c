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
    "Delete a contact",
    "Edit a contact",
    "Create backup"};

enum MainMenuItems
{
    QUIT = 0,
    ADD_NEW_CONTACT = 1,
    LIST_ALL_CONTACTS = 2,
    SEARCH_FOR_CONTACT = 3,
    DELTE_A_CONTACT = 4,
    EDIT_A_CONTACT = 5,
    CREATE_BACKUP = 6,
};
const char *search_menu_items[] = {
    "Search by Name",
    "Search by Number",
    "Fuzzy Search by Name",
    "Fuzzy Search by Number",
    "Go back to main menu",
};

enum SearhMenuItems
{
    SEARCH_BY_NAME = 0,
    SEARCH_BY_NUMBER = 1,
    FUZZY_SEARCH_BY_NAME = 2,
    FUZZY_SEARCH_BY_NUMBER = 3,
    GO_BACK_TO_MAIN_MENU = 4,
};

const char *list_menu_items[] = {
    "Simple List",
    "Table view",
    "Return to Main Menu",
};

enum ListMenuItems
{
    SIMPLE_LIST = 0,
    TABLE_VIEW = 1,
    RETURN_TO_MAIN_FROM_LIST = 2,
};

void main_menu(ContactContainer *container);

void add_new_contact(ContactContainer *container);

void list_all_contacts(ContactContainer *container);
void search_for_contact(ContactContainer *container);
Contact *search_for_contact_by_name(ContactContainer *container);

Contact *search_for_contact_by_number(ContactContainer *container);

Contact *fuzzy_search_for_contact_by_name(ContactContainer *container);
Contact *fuzzy_search_for_contact_by_number(ContactContainer *container);

void delete_contact(ContactContainer *container);

void create_backup(ContactContainer *container);

void list_as_table_print(ContactContainer *container);

void handle_list(ContactContainer *container);

void edit_contact(ContactContainer *container);
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
            handle_list(container);
            // list_all_contacts(container);
            break;
        case SEARCH_FOR_CONTACT:
            search_for_contact(container);
            break;
        case DELTE_A_CONTACT:
            delete_contact(container);
            break;
        case CREATE_BACKUP:
            create_backup(container);
            break;
        case EDIT_A_CONTACT:
            edit_contact(container);
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
    clear_console();
    if (contactContaier_get_size(container) == 0)
    {
        printf("There are no contacts\n");
    }
    else
    {
        contactContainer_for_all_contacts_do(container, print_contact);
    }
    press_any_key_to_continue("");
}

void delete_contact(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(search_menu_items, 5);
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
        case FUZZY_SEARCH_BY_NAME:
            contact_to_be_deleted = fuzzy_search_for_contact_by_name(container);
            break;
        case FUZZY_SEARCH_BY_NUMBER:
            contact_to_be_deleted = fuzzy_search_for_contact_by_number(container);
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
    MultipltChoiceMenu menu = create_multiple_choice_menu(search_menu_items, 4);
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
        case FUZZY_SEARCH_BY_NAME:
            fuzzy_search_for_contact_by_name(container);
            break;
        case FUZZY_SEARCH_BY_NUMBER:
            fuzzy_search_for_contact_by_number(container);
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

Contact *fuzzy_search_for_contact_by_name(ContactContainer *container)
{

    clear_console();
    char buffer[MAX_NAME_LENGTH + 5] = {0};
    bool running = true;
    Contact *searched_contact = INVALID_CONTACT;
    while (running)
    {
        clear_console();
        bool error = true;
        error = get_line_from_input(buffer, MAX_NAME_LENGTH, "Enter part of name to search: ");
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
        if (searched_contact != INVALID_CONTACT)
        {
            printf("An exact match was found!\n");
            print_contact(searched_contact);
            bool try_again = yes_no_query("Would you like to keep searching?");
            if (try_again)
            {
                continue;
            }
            break;
        }
        searched_contact = contactContainer_fuzzy_search_by_name(container, buffer);
        if (searched_contact == INVALID_CONTACT)
        {
            printf("No contacts similar were found\n");
            bool try_again = yes_no_query("Would you like to keep searching?");
            if (try_again)
            {
                continue;
            }
            break;
        }
        printf("Best match found\n");
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

Contact *fuzzy_search_for_contact_by_number(ContactContainer *container)
{
    clear_console();
    char buffer[PHONE_NUMBER_LENGTH + 5] = {0};
    bool running = true;
    Contact *searched_contact = INVALID_CONTACT;
    while (running)
    {
        clear_console();
        bool error = true;
        error = get_line_from_input(buffer, PHONE_NUMBER_LENGTH, "Enter part of number to search: ");
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
        if (searched_contact != INVALID_CONTACT)
        {
            printf("An exact match was found!\n");
            print_contact(searched_contact);
            bool try_again = yes_no_query("Would you like to keep searching?");
            if (try_again)
            {
                continue;
            }
            break;
        }
        searched_contact = contactContainer_fuzzy_search_by_number(container, buffer);
        if (searched_contact == INVALID_CONTACT)
        {
            printf("No contacts similar were found\n");
            bool try_again = yes_no_query("Would you like to keep searching?");
            if (try_again)
            {
                continue;
            }
            break;
        }
        printf("Best match found\n");
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

void create_backup(ContactContainer *container)
{
    const size_t max_path_length = 100;
    char file_path_buffer[100 + 5] = {0};
    while (true)
    {

        bool error = get_line_from_input(file_path_buffer, max_path_length, "Enter file name and path for backup: ");
        if (error)
        {
            if (!yes_no_query("The entered file path is of invalid format would you like to try again?"))
            {
                clear_console();
                return;
            }
            continue;
        }
        if (!yes_no_query("If a file already exists its contents will be overwritten. Would you like to proceed?"))
        {
            clear_console();
            return;
        }
        FILE *fptr = fopen(file_path_buffer, "w");
        if (fptr == NULL)
        {
            if (!yes_no_query("There was a problem with opening the file. Would you like to try again (Make sure file path is valid)?"))
            {
                clear_console();
                return;
            }
            clear_console();
            continue;
        }
        save_to_file(container, fptr);
        fclose(fptr);
        press_any_key_to_continue("Back up created sucessfully");
        clear_console();
        break;
    }
    clear_console();
}

void list_as_table_print(ContactContainer *container)
{

    clear_console();
    if (contactContaier_get_size(container) == 0)
    {
        printf("There are no contacts\n");
    }

    // press_any_key_to_continue("");
    print_table_seperator();
    table_header_print();
    print_table_seperator();
    print_table_seperator();
    for (int i = 0; i < contactContaier_get_size(container); i++)
    {
        const Contact *contact = contactContaier_get_contact(container, i);
        if (contact == INVALID_CONTACT)
        {
            continue;
        }
        table_row_print(contact);
        print_table_seperator();
    }
    press_any_key_to_continue("");
}

void handle_list(ContactContainer *container)
{
    MultipltChoiceMenu list_menu = create_multiple_choice_menu(list_menu_items, sizeof(list_menu_items) / sizeof(const char *));
    int choice = get_choice(&list_menu);
    while (true)
    {
        switch (choice)
        {
        case MULTIPLE_CHOICE_MENU_INVALID_CHOICE:
            press_any_key_to_continue("Your choice was invalid please select another option");
            clear_console();
            continue;
            break;
        case SIMPLE_LIST:
            list_all_contacts(container);
            clear_console();
            return;
            break;
        case TABLE_VIEW:
            list_as_table_print(container);
            clear_console();
            return;
            break;
        case RETURN_TO_MAIN_FROM_LIST:
            clear_console();
            return;
        }
        break;
    }
    clear_console();
}

void edit_contact(ContactContainer *container)
{
    clear_console();
    MultipltChoiceMenu menu = create_multiple_choice_menu(search_menu_items, 4);
    bool running = true;
    Contact *contact_to_be_edited = INVALID_CONTACT;
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
            contact_to_be_edited = search_for_contact_by_name(container);
            break;
        case SEARCH_BY_NUMBER:
            contact_to_be_edited = search_for_contact_by_number(container);
            break;
        case FUZZY_SEARCH_BY_NAME:
            contact_to_be_edited = fuzzy_search_for_contact_by_name(container);
            break;
        case FUZZY_SEARCH_BY_NUMBER:
            contact_to_be_edited = fuzzy_search_for_contact_by_number(container);
            break;
        case GO_BACK_TO_MAIN_MENU:
            break;
        }
        clear_console();
        if (contact_to_be_edited == INVALID_CONTACT)
        {
            bool request = yes_no_query("No such contact was found would you like to try again");
            if (request)
            {
                clear_console();
                continue;
            }
            break;
        }
        printf("The following contacts information will be edited\n");
        print_contact(contact_to_be_edited);
        bool request = yes_no_query("Are you sure you want to proceed?");
        if (!request)
        {
            press_any_key_to_continue("Returning");
            break;
        }
        bool error = false;
        Contact updated_contact = edit_contact_from_ui(contact_to_be_edited, &error);
        if (error)
        {
            bool try_again = yes_no_query("One of the edited fields is of incorrect format. Would you like to try again?");
            if (try_again)
            {
                clear_console();
                continue;
            }
            break;
        }
        Contact temp_copy_of_old = {0};
        memcpy(&temp_copy_of_old, contact_to_be_edited, sizeof(Contact)); // creating a backup copy of the contact
        contactContainer_delete_contact(container, contact_to_be_edited);
        if (contactContianer_search_contact_by_name(container, updated_contact.name) != CONTACT_DOES_NOT_EXIST)
        {
            running = yes_no_query("A contact by the updated name already exist,This is not allowed,Would you like try again?");
            clear_console();
            contactContianer_push_contact(container, &temp_copy_of_old);
            continue;
        }
        printf("The new update is valid. The following changes will be made\n");

        printf("---------------------------------------\n");
        printf("name\t\t: %s->%s\n", temp_copy_of_old.name, updated_contact.name);
        printf("phone\t\t: %s->%s\n", temp_copy_of_old.phone, updated_contact.phone);
        printf("email\t\t: %s->%s\n", temp_copy_of_old.email, updated_contact.phone);
        printf("address\t\t: %s->%s\n", temp_copy_of_old.address, updated_contact.address);
        printf("---------------------------------------\n");
        if (!yes_no_query("Are the changes satisfactory or do you want to try again?"))
        {
            clear_console();
            contactContianer_push_contact(container, &temp_copy_of_old);
            continue;
        }
        contactContianer_push_contact(container, &updated_contact);
        press_any_key_to_continue("The updates was successfull");
        break;
    }
    clear_console();
}