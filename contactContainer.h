#include "contactManager.h"
typedef struct ContactContainer ContactContainer;

ContactContainer *contactContainer_create(size_t intial_capacity);

void contactContianer_destroy(ContactContainer *container);

void contactContianer_push_contact(ContactContainer *container, const Contact *contact);

Contact *contactContianer_search_contact_by_name(ContactContainer *container, char *name);

Contact *contactContianer_search_contact_by_number(ContactContainer *continaer, char *number);

int contactContainer_delete_contact(ContactContainer *contianer, Contact *contact);