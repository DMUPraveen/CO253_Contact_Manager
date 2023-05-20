
#include "ui.h"

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

int get_int(bool *error)
{
    int n = 0;
    int v = scanf("%d", &n);
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
    int choice = get_int(&parse_error);

    bool option_error = !valid_choice(menu, choice);
    if (parse_error || option_error)
    {
        return MULTIPLE_CHOICE_MENU_INVALID_CHOICE;
    }
    print_open_close_banner();
    return choice;
}