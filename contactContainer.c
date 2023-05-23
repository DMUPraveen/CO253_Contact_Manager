#include "contactContainer.h"
#include "contactManager.h"

#define TRIE_NODE_DOES_NOT_EXIS NULL
#define TRIE_NODE_LIST_ITEM_DOES_NOT_EXIST NULL
typedef struct contactContainer
{
    // models an opaque type that conatins the contact - This is the Trie base implpementation
    struct TrieNode *head;

} contactContainer;

typedef struct TrieNode
{
    // models a data structre
    char letter; // the letter corresponding to the node, nullbyte indicates a lead node
    union
    {
        contact *ct; // the contact stored in the TrieNode if it is a lead node
        const struct TNList *list;
    };

} TrieNode;

typedef struct TNList
{
    // models a doubly linked list of TrieNodes
    struct TNList *prev;
    struct TNList *next;
    const struct TrieNode *item; // does not own the item

} TNList;

bool is_leaf_node(TrieNode *tn);
contact *get_contact(TrieNode *tn);
TrieNode *find_trienode_with_letter_in_list(TNList *list_head, char letter);
void push_item(TNList **list_head, TrieNode *item); // modifies the list head

TrieNode *pop_item_and_return_payload(TNList *list_item);
TrieNode *get_payload(TNList *list_item);
TrieNode *create_trie_node_leaf(contact *ct);
TrieNode *create_trie_node_non_leaf(char letter);
TNList *create_new_TNList_item(const TrieNode *item);

bool is_leaf_node(TrieNode *tn)
{
    return (tn->letter == '\0');
}

contact *get_contact(TrieNode *tn)
{
    return tn->ct;
}

TrieNode *get_payload(TNList *list_item)
{
    return (TrieNode *)(list_item->item); // at this point we may allow the user to modify it
}

TrieNode *find_trienode_with_letter_in_list(TNList *list_head, char letter)
{
    TNList *current_item = list_head; // iterator variable
    while (current_item != TRIE_NODE_LIST_ITEM_DOES_NOT_EXIST)
    // while we haven reached the end of the list
    {
        TrieNode *current_trie_node = get_payload(current_item);
        if (current_trie_node->letter == letter) // if the letter of the payload is the letter we are searching
        {
            // we are done
            return current_trie_node;
        }
        current_item = current_item->next; // increment the iterator
    }
    return TRIE_NODE_DOES_NOT_EXIS; // if we reach the end end of the list then the item
    // does not exist
}

void push_item(TNList **list_head, TrieNode *item)
{
    // pushes an items to the list defined by the list_head
    // if the list head is null it will create a new list
    // if the list head is not null then it will modify it with a new head that containes
    // the newly added item
    TNList *new_head = create_new_TNList_item(item);
    new_head->next = *list_head;   // creating forwad link
    (*list_head)->prev = new_head; // creating backward link
    *list_head = new_head;         // modify head
}

TNList *create_new_TNList_item(const TrieNode *item)
{
    // does not take ownership of the item
    TNList *new_list_item = calloc(1, sizeof(TNList));
    // at creation it is not connected this is the responsibilty of the caller
    new_list_item->prev = TRIE_NODE_LIST_ITEM_DOES_NOT_EXIST;
    new_list_item->next = TRIE_NODE_LIST_ITEM_DOES_NOT_EXIST;
    new_list_item->item = item;
    return new_list_item;
}