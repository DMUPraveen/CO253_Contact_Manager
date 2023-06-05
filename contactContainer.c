#include <string.h>
#include "contactContainer.h"
#include "contact.h"

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
Contact *contactContianer_search_contact_by_name(ContactContainer *container, char *name)
{
    for (int i = 0; i < container->size; i++)
    {
        if (strcmp(name, container->contact_array[i].name) == 0)
        {
            return (container->contact_array) + i;
        }
    }
    return CONTACT_DOES_NOT_EXIST;
}

Contact *contactContianer_search_contact_by_number(ContactContainer *container, char *name)
{
    for (int i = 0; i < container->size; i++)
    {
        if (strcmp(name, container->contact_array[i].phone) == 0)
        {
            return (container->contact_array) + i;
        }
    }
    return CONTACT_DOES_NOT_EXIST;
}

void swap_contacts(Contact *contact1, Contact *contact2)
{
    Contact temp = *contact1;
    *contact1 = *contact2;
    *contact2 = temp;
}

bool contactContainer_delete_contact(ContactContainer *container, Contact *contact)
{
    /*

        returns whether the remove operation was sucessful or not

        Caution! - contact should be one returned from a find operations and that is known
        to be inside the container, passing random contact pointer will lead to undefined behaviour
        whether the contact that is passed is within the container is not checked by this function
        it is responsibility of the user to ensure that it is

        This also changes the order of the elements in the array
    */

    // swap with the last element of the array
    if (contact == INVALID_CONTACT)
    {
        return false;
    }
    swap_contacts(contact, (container->contact_array) + (container->size - 1));
    container->size--;
    if (container->size < (container->capacity) / 4) // when the array is qauter full
    {
        contactContaier_resize_array(container, container->capacity / 2); // resize it to half capcity
    }
    return true;
}

const char *serializer_format = "{'%s','%s','%s','%s'}\n";
void save_to_file(ContactContainer *container, FILE *fptr)
{
    if (fptr == NULL)
    {
        return;
    }
    for (int i = 0; i < contactContaier_get_size(container); i++)
    {
        Contact *current_contact = &(container->contact_array[i]);
        fprintf(fptr, serializer_format, current_contact->name, current_contact->phone, current_contact->email, current_contact->address);
    }
}

void load_from_file(ContactContainer *container, FILE *fptr)
{

    const char *deserializer_format = "{'%[^']','%[^']','%[^']','%[^']'}%*c";
    if (fptr == NULL)
    {
        return;
    }
    while (true)
    {
        Contact new_contact = {0};
        // char buf1[20] = {0};
        // char buf2[20] = {0};
        // char buf3[20] = {0};
        // char buf4[20] = {0};
        int elements_read = fscanf(fptr, deserializer_format, new_contact.name, new_contact.phone, new_contact.email, new_contact.address);

        if (elements_read != 4)
        {
            break;
        }
        contactContianer_push_contact(container, &new_contact);
    }
}