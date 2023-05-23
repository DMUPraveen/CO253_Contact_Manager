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
        struct TNList *list;
    };

} TrieNode;

typedef struct TNList
{
    // models a doubly linked list of TrieNodes
    struct TNList *prev;
    struct TNList *next;
    struct TrieNode *item;

} TNList;

bool is_leaf_node(TrieNode *tn);
contact *get_contact(TrieNode *tn);
TrieNode *find_trienode_with_letter_in_list(TNList *list_head, char letter);
bool push_item(TNList **list_head, TrieNode *item); // modifies the list head
TrieNode *pop_item_and_return_payload(TNList *list_item);
TrieNode *get_payload(TNList *list_item);
TrieNode *create_trie_node_leaf(contact *ct);
TrieNode *create_trie_node_non_leaf(char letter);

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
    return list_item->item;
}

TrieNode *find_trienode_with_letter_in_list(TNList *list_head, char letter)
{
    TNList *current_item = list_head;
    while (current_item != TRIE_NODE_LIST_ITEM_DOES_NOT_EXIST)
    {
        TrieNode *current_trie_node = get_payload(current_item);
        if (current_trie_node->letter == letter)
        {
            return current_trie_node;
        }
        current_item = current_item->next;
    }
    return TRIE_NODE_DOES_NOT_EXIS;
}