#include "contactContainer.h"
#include "contactManager.h"

struct ContactContainer
{

    Contact *contact_array;
    int size;
    int capacity;
};

ContactContainer create_contactContainer(int intial_capacity)
{
    ContactContainer new_container = {
        .contact_array = NULL,
        .size = 0,
        .capacity = intial_capacity,
    };
    new_container.contact_array = calloc(new_container.capacity, sizeof(Contact));
    return new_container;
}

void destroy_contactContainer(ContactContainer *container)
{
    free(container->contact_array);
    container->contact_array = NULL;
    container->size = 0;
    container->capacity = 0;
}