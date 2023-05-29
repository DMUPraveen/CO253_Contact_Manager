
#include "contact.h"
#include "string.h"
const phoneNumber min_phone_number = 1000000000;
const phoneNumber max_phone_number = 9999999999;
bool validate_phone_number(char *number)
{
    if (strlen(number) != 10)
    {
        return false;
    }
    for (int i = 0; i < 10; i++)
    {
        if (number[i] < '0' || number[i] > '9')
        {
            return false;
        }
    }
    return true;
}

bool validate_name(char *name)
{
    return (strlen(name) <= MAX_NAME_LENGTH);
}

bool validate_address(char *address)
{
    return (strlen(address) <= MAX_ADRESS_LENGTH);
}

bool validate_email(char *email)
{
    if ((strlen(email) >= MAX_EMAIL_LENGTH))
    {
        return false;
    }

    char mail[MAX_EMAIL_LENGTH];
    char domain[MAX_EMAIL_LENGTH];
    char top_level_domain[MAX_EMAIL_LENGTH];

    const char *email_format = "%[^@\n]@%[^.\n].%[^.\n]";
    int ret_val = sscanf(email, email_format, mail, domain, top_level_domain);
    if (ret_val != 3)
    {
        return false;
    }
    return true;
}

void debug_print_contact(const Contact *con)
{
    // printf("%d\n", sizeof(con->phone));
    printf("******************************\n");
    printf("phone_number %s\n", con->phone);
    printf("name %s\n", con->name);
    printf("address %s\n", con->address);
    printf("email %s\n", con->email);
    printf("******************************\n");
}

bool debug_equals(Contact *con1, Contact *con2)
{
    if (con1 == NULL || con2 == NULL)
    {
        return false;
    }
    if (strcmp(con1->address, con2->address))
    {
        return false;
    }
    if (strcmp(con2->email, con2->email))
    {
        return false;
    }
    if (strcmp(con1->phone, con2->phone))
    {
        return false;
    }
    if (strcmp(con1->name, con2->name))
    {
        return false;
    }
    return true;
}