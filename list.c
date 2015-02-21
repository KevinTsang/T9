/**
 * Kevin Tsang
 * CSE 374
 * 2/20/2015
 * A linked list implementation
 * that stores characters.
 */

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

// takes the head of a list and an index and gets the word at that index 
char* list_get(List* head, int index) {
  List* current = head;
  for (int i = 0; i < index; i++) {
    if (current == NULL) {
      fputs("The index is longer than the size of the list.", stderr);
      break;
    }
    current = current->tail;
  }
  return current->val;
}

// free a whole list, takes the head of a list as input 
void list_free(struct List* lst) {
  while(lst != NULL) {
    struct List* next = lst->tail; 
    free(lst);
    lst = next;
  }
}
