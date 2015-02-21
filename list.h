/**
 * Kevin Tsang
 * CSE 374
 * 2/20/2015
 * Linked List header file*/

// a Linked List node which stores
// a word and a pointer to the next
// node
typedef struct List {
  char* val;
  struct List * tail;
} List;

// return a new node containing character array x and a null tail field
List* list_new(char* x);

// takes the head of a list and an index and gets the word at that index 
char* list_get(List* head, int index);

// free a whole list, takes the head of a list as input 
void list_free(List* lst);
