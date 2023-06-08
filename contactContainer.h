#pragma once
#include "contact.h"
#define INVALID_CONTACT NULL
#define CONTACT_DOES_NOT_EXIST NULL

typedef struct ContactContainer ContactContainer;

ContactContainer *contactContainer_create(size_t intial_capacity);

size_t contactContaier_get_size(ContactContainer *container);

void contactContianer_destroy(ContactContainer *container);

void contactContianer_push_contact(ContactContainer *container, const Contact *contact);

Contact *contactContianer_search_contact_by_name(ContactContainer *container, char *name);

Contact *contactContianer_search_contact_by_number(ContactContainer *continaer, char *number);

bool contactContainer_delete_contact(ContactContainer *container, Contact *contact);

void contactContainer_for_all_contacts_do(ContactContainer *container, void (*func)(const Contact *));

void save_to_file(ContactContainer *container, FILE *fptr);

void load_from_file(ContactContainer *container, FILE *fptr);

Contact *contactContainer_fuzzy_search_by_name(ContactContainer *container, const char *name);

Contact *contactContainer_fuzzy_search_by_number(ContactContainer *container, const char *num_str);

const Contact *contactContaier_get_contact(ContactContainer *container, size_t index);