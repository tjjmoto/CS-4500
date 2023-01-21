#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(){

}

/* Allocate space for a new list and set its head to NULL.
Returns the created list if successful , NULL otherwise . */
list* createlist() {

};

/* Allocates a new node and copies the s t r i n g from item to t h i s node
18 ∗ ( use malloc , strlen , and strncpy ; or try strdup ) . Adds t h i s new node
19 ∗ to end of the l i s t l l . Returns 0 i f successful , non−zero otherwise . */
int addtolist(list* ll, char* item) {

};

/* Removes the head of the l i s t l l , extracts the s t r i n g stored in the head ,
23 ∗ and returns a pointer to t h i s s t r i n g . Also f r e e s the removed head node . */
char* removefromlist(list* ll) {

};

/* Prints every s t r i n g in each node of the l i s t l l , with a new l i n e
∗ character at the end of each s t r i n g */
void printlist(list* ll) {

};

/* Flushes ( c l e a r s ) the e n t i r e l i s t and re−i n i t i a l i z e s the l i s t . The passed
∗ pointer l l should s t i l l point to a valid , empty l i s t when t h i s function
∗ returns . Any memory a l l o c a t e d to store nodes in the l i s t should be freed .
*/
void flushlist(list* ll) {

};

/* De−a l l o c a t e s a l l data f o r the l i s t . Ensure a l l memory a l l o c a t e d f o r l i s t
l l i s freed , including any a l l o c a t e d s t r i n g s and l i s t l l i t s e l f . */
void freelist (list* ll) {

};