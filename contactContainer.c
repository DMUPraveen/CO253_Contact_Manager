#include "contactContainer.h"
#include "contactManager.h"

struct ContactContainer
{

    Contact *contact_array;
    size_t size;
    size_t capacity;
};

ContactContainer *contactContainer_create(size_t intial_capacity)
{
    ContactContainer *new_container = calloc(1, sizeof(ContactContainer));
    new_container->capacity = intial_capacity;
    new_container->contact_array = calloc(new_container->capacity, sizeof(Contact));
    new_container->size = 0;
    return new_container;
}

void contactContianer_destroy(ContactContainer *container)
{
    free(container->contact_array);
    free(container);
}

void contactContaier_resize_array(ContactContainer *container, size_t new_container_capacity)
{
    if (new_container_capacity != 0)
    {

        container->contact_array = realloc(container->contact_array, new_container_capacity * sizeof(Contact));
        container->capacity = new_container_capacity;
    }
}
void contactContianer_push_contact(ContactContainer *container, const Contact *contact)
{
    // does not take ownership of the contact but copies the data over
    // caller is responisble for managinf the memory of contact
    if (container->capacity == 0 || container->capacity == container->size)
    {
        // resizing stratergy -- if empty make it 1, if full double
        size_t new_container_capacity = (container->capacity == 0) + (container->capacity) * 2;
        contactContaier_resize_array(container, new_container_capacity);
    }
    container->contact_array[container->size] = *contact;
    container->size++;
}

size_t contactContaier_get_size(ContactContainer *container)
{
    return container->size;
}

void contactContainer_for_all_contacts_do(ContactContainer *container, void (*func)(const Contact *))
{
    for (int i = 0; i < container->size; i++)
    {
        func((container->contact_array) + i);
    }
}