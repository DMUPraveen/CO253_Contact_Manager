#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DEFAULT_CONTACT_CONTAINER_SIZE 5
#define MAX_NAME_LENGTH 20
#define MAX_ADRESS_LENGTH 50
#define MAX_EMAIL_LENGTH 30
#define INVALID_PHONE_NUMBER -1
#define PHONE_NUMBER_LENGTH 10
typedef long long phoneNumber;
typedef struct
{
    char phone[PHONE_NUMBER_LENGTH + 5];
    char name[MAX_NAME_LENGTH + 5];
    char address[MAX_ADRESS_LENGTH + 5];
    char email[MAX_EMAIL_LENGTH + 5];
} Contact;

bool validate_phone_number(char *number);
bool validate_name(char *name);
bool validate_address(char *address);
bool validate_email(char *email);
void debug_print_contact(const Contact *con);

bool debug_equals(Contact *con1, Contact *con2);