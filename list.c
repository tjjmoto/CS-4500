#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//node *head;
//node *current = NULL;
list *llist;

int main(){

}

/* Allocate space for a new list and set its head to NULL.
Returns the created list if successful , NULL otherwise . */
list* createlist() {
    addtolist(llist, "A");
    // TODO: Allocate space for new list
    //head = malloc(sizeof(llist));
    //llist->head = head;

    if (llist->head != NULL) {
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
    struct Node *temp = ll;

    if (temp != NULL && temp->item == ll->head) {
        // Change head
        ll->head = temp->next;
        free(temp);
        return temp->next;
    } 
};

/* Prints every string in each node of the list ll , with a new line
character at the end of each string */
void printlist(list* ll) {

};

/* Flushes (clears) the entirlist and re−initializes the list . The passed
∗ pointer ll should still point to a valid , empty list when this function
∗ returns . Any memory allocated to store nodes in the list should be freed .
*/
void flushlist(list* ll) {

};

/* De−allocates all data for the list . Ensure all memory allocated for list
ll is freed , including any al located strings and list ll itself . */
void freelist (list* ll) {

};