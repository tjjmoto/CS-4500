//Declaring all the structs
typedef struct Node node ;
struct Node {
char *item ;
node *next ;
};

typedef struct List {
node *head ;
}list;

list* createlist();
int addtolist(list*, char*);
char* removefromlist(list*);
void printlist(list*);
void flushlist(list*);
void freelist (list*);