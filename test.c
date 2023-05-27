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
    phone[0] = '3'; // to distinguish the randomly generated numbers -> will always be of the form 3xxxxxxxxx;

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
void test_adding_elements_and_resize()
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
    contactContianer_destroy(container);

    // printf("Printing all contacts\n");
    // contactContainer_for_all_contacts_do(container, debug_print_contact);
}

void test_finding_elements_that_were_added_by_name()
{
    ContactContainer *container = contactContainer_create(10);
    Contact random_contact = create_random_contact();
    contactContianer_push_contact(container, &random_contact);
    Contact *returned_contact = contactContianer_search_contact_by_name(container, random_contact.name);
    check(returned_contact != INVALID_CONTACT, "ADDED CONTACT EXISTS");
    check(debug_equals(returned_contact, &random_contact), "ADDED CONTACT IS EQUAL TO ORIGINAL");

    Contact other_contacts[20] = {0};
    for (int i = 0; i < 20; i++)
    {
        other_contacts[i] = create_random_contact();
        contactContianer_push_contact(container, other_contacts + i);
    }
    bool all_exist = true;
    bool all_equal = true;
    for (int i = 0; i < 20; i++)
    {
        Contact *found_contact = contactContianer_search_contact_by_name(container, other_contacts[i].name);
        all_exist &= (found_contact != INVALID_CONTACT);
        all_equal &= (debug_equals(&other_contacts[i], found_contact));
    }
    check(all_exist, "ALL ADDED CONTACTS EXIST");
    check(all_equal, "ALL ADDED CONTACTS HAVE ORIGINAL DATA");

    char *non_existent_name = "nonExistentName";
    Contact *found_contact = contactContianer_search_contact_by_name(container, non_existent_name);
    check(found_contact == INVALID_CONTACT, "CONTACT NOT FOUND TEST");
    contactContianer_destroy(container);
}

void test_finding_elements_that_were_added_by_number()
{
    ContactContainer *container = contactContainer_create(10);
    Contact random_contact = create_random_contact();
    contactContianer_push_contact(container, &random_contact);
    Contact *returned_contact = contactContianer_search_contact_by_number(container, random_contact.phone);
    check(returned_contact != INVALID_CONTACT, "ADDED CONTACT EXISTS");
    check(debug_equals(returned_contact, &random_contact), "ADDED CONTACT IS EQUAL TO ORIGINAL");

    Contact other_contacts[20] = {0};
    for (int i = 0; i < 20; i++)
    {
        other_contacts[i] = create_random_contact();
        contactContianer_push_contact(container, other_contacts + i);
    }
    bool all_exist = true;
    bool all_equal = true;
    for (int i = 0; i < 20; i++)
    {
        Contact *found_contact = contactContianer_search_contact_by_number(container, other_contacts[i].phone);
        all_exist &= (found_contact != INVALID_CONTACT);
        all_equal &= (debug_equals(&other_contacts[i], found_contact));
    }
    check(all_exist, "ALL ADDED CONTACTS EXIST");
    check(all_equal, "ALL ADDED CONTACTS HAVE ORIGINAL DATA");

    char *non_existent_number = "0719600222"; // generated contacts have numbers that start with 3;
    Contact *found_contact = contactContianer_search_contact_by_number(container, non_existent_number);
    check(found_contact == INVALID_CONTACT, "CONTACT NOT FOUND TEST");
    contactContianer_destroy(container);
}
int main()
{
    run_test_suite(test_adding_elements_and_resize, "CONTAINER_ADDITION");
    run_test_suite(test_finding_elements_that_were_added_by_name, "FINDING CONTACTS BY NAME");
    run_test_suite(test_finding_elements_that_were_added_by_number, "FINDING CONTACTS BY NAME");

    return 0;
}