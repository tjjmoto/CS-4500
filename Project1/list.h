//Declaring all the structs
typedef struct Node node ;

//a Node is part of a list with a pointer to data stored as char in "item" and with a pointer to the next Node stored in "next"
struct Node {
char *item ;
node *next ;
};

//a List is a struct in which there is a head node which points to the front of the list.
typedef struct List {
node *head ;
}list;


//fuctions for manipulating a list
list* createlist();
int addtolist(list*, char*);
char* removefromlist(list*);
void printlist(list*);
void flushlist(list*);
void freelist (list*);
