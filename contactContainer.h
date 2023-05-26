#include "contactManager.h"
typedef struct ContactContainer ContactContainer;

ContactContainer create_contactContainer(int intial_capacity);

void push_contact(ContactContainer *container, Contact *con);

Contact *search_contact_by_name(ContactContainer *container, char *name);

Contact *search_contact_by_number(ContactContainer *continaer, char *number);

int delete_contact(ContactContainer *contianer, Contact *contact);