#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactManager.h"
#include "contactContainer.h"

Contact create_random_contact()
{
    Contact new_contact;
    sprintf(new_contact.name, "test_name_%d", rand() % 100);
    sprintf(new_contact.address, "test_adress_%d", rand() % 100);
    sprintf(new_contact.email, "test_%d@other_%d.com", rand() % 100, rand() % 100);
    char phone[11] = {0};
    for (int i = 0; i < 10; i++)
    {
        phone[i] = rand() % 10 + '0';
    }

    strcpy(new_contact.phone, phone);
    return new_contact;
}

void check(bool expression, char *test)
{
    char *status = (expression) ? "PASSED" : "FAILED";
    printf("%s -- %s\n", test, status);
}

void run_test_suite(void (*test_function)(), char *test_collection_name)
{
    printf("Running ----------- %s ------------\n", test_collection_name);
    test_function();
    printf("-----------------------------------\n");
    printf("\n");
}
void test_test_suite()
{
    ContactContainer *container = contactContainer_create(10);
    check(contactContaier_get_size(container) == 0, "INITIAL_SIZE == 0");
    Contact random_contact = create_random_contact();
    contactContianer_push_contact(container, &random_contact);
    check(contactContaier_get_size(container) == 1, "AFTER_ADDING_ONE == 1");
    for (int i = 0; i < 8; i++)
    {
        Contact r = create_random_contact();
        contactContianer_push_contact(container, &r);
    }
    check(contactContaier_get_size(container) == 9, "NO_RESIZE_ADDITION_CHECK");
    for (int i = 0; i < 11; i++)
    {
        Contact r = create_random_contact();
        contactContianer_push_contact(container, &r);
    }
    check(contactContaier_get_size(container) == 20, "WITH_RESIZE_ADDITION_CHECK");

    // printf("Printing all contacts\n");
    // contactContainer_for_all_contacts_do(container, debug_print_contact);
}
int main()
{
    run_test_suite(test_test_suite, "CONTAINER_ADDITION");
    return 0;
}