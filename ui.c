#include "ui.h"
#include "contactManager.h"

void clear_input_stream()
{
    while (1)
    {
        char c = getchar();
        if (c == '\n' || c == EOF)
        {
            break;
        }
    }
}

bool get_line_from_input(char *buffer, int max_number, const char *message)
{
    printf("%s", message);
    char *result = fgets(buffer, max_number + 2, stdin);
    if (result == NULL)
    {
        return true;
    }
    // removing the traingline new line
    if (buffer[strlen(buffer) - 1] != '\n')
    {
        clear_input_stream();
        return true; // too many characters were given
    }

    buffer[strlen(buffer) - 1] = 0; // replacing the new line character that was read with a new one
    return false;
}
void print_open_close_banner()
{
    const char *banner_open_close = "--------------------------------------------------------\n";
    printf("%s", banner_open_close);
}
void print_title_banner()
{
    const char *title_banner = "CONTACT MANAGEMENT SYSTEM\n";
    print_open_close_banner();
    printf("%s", title_banner);
    print_open_close_banner();
}

long long get_int(const char *message, bool *error)
{
    printf("%s", message);
    long long n = 0;
    long long v = scanf("%lld", &n);
    *error = false;
    if (v != 1)
    {
        *error = true;
    }
    clear_input_stream();
    return n;
}

void clear_console()
{
    system("clear");
}

MultipltChoiceMenu create_multiple_choice_menu(const char **menu_items, int number_of_items)
{
    /*
    Creates a Multiple choice menu,
    number_of_items must be equal to the number of menu_items
    this does not take ownership of menu_items
    */
    MultipltChoiceMenu menu = {
        .menu_items = menu_items,
        .size = number_of_items};

    return menu;
}

void display_menu(MultipltChoiceMenu *menu)
{
    for (int i = 0; i < menu->size; i++)
    {
        printf("%d. %s\n", i, menu->menu_items[i]);
    }
}

bool valid_choice(MultipltChoiceMenu *menu, int choice)
{
    return (0 <= choice && choice < menu->size);
}

int get_choice(MultipltChoiceMenu *menu)
{
    /*
    shows the menu and gets a choice from the user
    if the enterd value is an invalid option then the get_choice will return MULTIPLE_CHOICE_MENU_INVALID_CHOICE
    */
    display_menu(menu);
    print_open_close_banner();
    const char *enter_option_qeury = "Enter Option [0-%d]: ";
    printf(enter_option_qeury, menu->size);
    bool parse_error = false;
    int choice = get_int("", &parse_error);

    bool option_error = !valid_choice(menu, choice);
    if (parse_error || option_error)
    {
        return MULTIPLE_CHOICE_MENU_INVALID_CHOICE;
    }
    print_open_close_banner();
    return choice;
}

bool get_phone_number_from_ui(char *phone_number)
{
    bool phone_error = false;
    const char *phone_number_query = "Enter the phone number[must have 10 digits]: ";
    phone_error = get_line_from_input(phone_number, PHONE_NUMBER_LENGTH, phone_number_query);
    phone_error = phone_error | (!validate_phone_number(phone_number));
    return phone_error;
}

bool get_name(char *name_buffer)
{

    const char *name_query = "Enter the name [10 characters max]:";
    bool error = get_line_from_input(name_buffer, MAX_NAME_LENGTH, name_query);
    error |= !validate_name(name_buffer);
    return error;
}

bool get_address(char *address_buffer)
{

    const char *address_query = "Enter the address [50 characters max]:";
    bool error = get_line_from_input(address_buffer, MAX_ADRESS_LENGTH, address_query);
    error |= !validate_address(address_buffer);
    return error;
}

bool get_email(char *email_buffer)
{
    const char *email_query = "Enter the email address [30 characters max]:";
    bool error = get_line_from_input(email_buffer, MAX_EMAIL_LENGTH, email_query);
    error |= !validate_email(email_buffer);
    return error;
}

Contact get_contact_from_ui(bool *error)
{
    const char *enter_new_contact_qeury = "CREATE NEW CONTACT\n";
    print_open_close_banner();
    printf("%s", enter_new_contact_qeury);
    print_open_close_banner();

    Contact new_contact = {
        {0}, {0}, {0}, {0}};
    *error = get_phone_number_from_ui(new_contact.phone);
    if (*error)
    {
        return new_contact;
    }
    *error = get_name(new_contact.name);
    if (*error)
    {
        return new_contact;
    }
    *error = get_email(new_contact.email);
    if (*error)
    {
        return new_contact;
    }
    *error = get_address(new_contact.address);
    if (*error)
    {
        return new_contact;
    }
    return new_contact;
}