#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"

int main () {


    list *llist = createlist();
    
    if(llist != NULL)
    { 
        int reply = addtolist(llist, "H");
        if(reply!=0)
        {
            printf("Failed to add to List\n");
        }
        addtolist(llist, "E");
        addtolist(llist, "L");
        addtolist(llist, "L");
        addtolist(llist, "O");

        printlist(llist);

        removefromlist(llist);
        removefromlist(llist);


        printlist(llist);

        flushlist(llist);

        addtolist(llist, "E");
        addtolist(llist, "L");
        addtolist(llist, "L");
        
       	reply = addtolist(llist, 6);
        if(reply!=1)
        {
            printf("Failed to add to List\n");
        }

        // Seg Fault (null input)
        printlist(llist);

        freelist (llist);

    }
    else
    {
       printf("Failed to make List\n");
    }
};
