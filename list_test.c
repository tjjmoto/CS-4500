#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main () {


    list *llist = createlist();
    
    if(llist != NULL)
    { 
        // This part shows that adding to the list functions correctly
        int reply = addtolist(llist, "H");
        if(reply!=0)
        {
            printf("Failed to add to List\n");
        }
        addtolist(llist, "E");
        addtolist(llist, "L");
        addtolist(llist, "L");
        addtolist(llist, "O");

        // This part shows that printing the list previously made works correctly
        printlist(llist);

        // This part shows that removing the items from the list works correctly
        removefromlist(llist);
        removefromlist(llist);

        printlist(llist);

        // This part shows that the list is flushed (not freed) meaning everything is allocated still for adding more strings to list.
        flushlist(llist);

        addtolist(llist, "E");
        addtolist(llist, "L");
        addtolist(llist, "L");

        addtolist(llist, "/");

        // Seg Fault because the input is not of char type and fails to print an int
        printlist(llist);

        // This fails (seg faults) because it shows that the list is no longer allocated in memory AKA Freed (Working as it should)
        freelist (llist);
        int ensureFreed = addtolist(llist, "This is a string");
        printlist(llist);

        // This part shows that create list makes a new list after being completely removed from memory (no issues with 2x of the same list)
        list *llist = createlist();
        addtolist(llist, "New List");
        printlist(llist);
    }
    else
    {
       printf("Failed to make List\n");
    }
    return 0;
};
