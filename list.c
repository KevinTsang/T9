
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// a single list node
typedef struct List {
  char* val;
  struct List * tail;
} List;

// return a new node containing character array x and a null tail field
struct List* list_new(char* x) {
  struct List* ans = 
    (struct List*)malloc(sizeof(struct List));
  ans->val = x;
  ans->tail = NULL;
  return ans;
}

char* list_get(List* head, int index) {
  List* current = head;
  for (int i = 0; i < index; i++) {
    current = current->tail;
  }
  return current->val;
}

// free the whole list; better not use any other pointers
// to any list elements (and better not have a circular list)
void list_free(struct List* lst) {
  while(lst != NULL) {
    struct List* next = lst->tail; // must precede next statement
    free(lst);
    lst = next;
  }
}
