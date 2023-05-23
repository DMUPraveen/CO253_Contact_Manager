#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "contactManager.h"

typedef struct contactContainer contactContainer;
/*
contactContainer models a container that contains contacts and models the following operations
1. Insertin contacts
2. Deleting contacts
3. Searching for contacts


*/

bool insert_contact(contactContainer *container, contact *ct); // does not take ownership of contact
bool delte_contact(contactContainer *container, char *name);
contact *search_contact(contactContainer *container, char *name);
