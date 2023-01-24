#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list *llist;


/* Allocate space for a new list and set its head to NULL.
Returns the created list if successful , NULL otherwise . */
list* createlist() {
    llist = (struct List*)malloc(sizeof(struct List));

	llist->head = NULL;
    if (llist->head == NULL) {
        return llist;
    } else {
        return NULL;
    }
};

/* Allocates a new node and copies the string from item to this node
( use malloc , strlen , and strncpy ; or try strdup ) . Adds this new node
to end of the list ll . Returns 0 if successful , non−zero otherwise . */
int addtolist(list* ll, char* item) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    
    new_node->item = item;
    new_node->next = ll->head;
    ll->head = new_node;

    if (new_node->item == ll->head->item) {
        // Successful
        return 0;
    } else {
        // Not successful
        return 1;
    }

};

/* Removes the head of the list ll , extracts the string stored in the head ,
and returns a pointer to this string . Also frees the removed head node . */
char* removefromlist(list* ll) {
    if (ll->head != NULL) {
        // Change head
        ll->head = ll->head->next;
        return ll->head->next->item;
    } 
};

/* Prints every string in each node of the list ll , with a new line
character at the end of each string */
void printlist(list* ll) {
    node *temp;
    temp = ll->head;
    while (ll->head != NULL) {
        printf(" %s \n", ll->head->item);
        ll->head = ll->head->next;
    }
    ll->head = temp;
};

/* Flushes (clears) the entirelist and re−initializes the list . The passed
∗ pointer ll should still point to a valid , empty list when this function
∗ returns . Any memory allocated to store nodes in the list should be freed .
*/
void flushlist(list* ll) 
{
    
    while (ll->head != NULL) {
        node *temp;
        temp = ll->head;
        ll->head = ll->head->next;
        free(temp);
    }
    createlist();
};

/* De−allocates all data for the list . Ensure all memory allocated for list
ll is freed , including any al located strings and list ll itself . */
void freelist (list* ll) {
    while (ll->head != NULL) {
        node *temp;
        temp = ll->head;
        ll->head = ll->head->next;
        free(temp);
    }
    free(ll);
};
