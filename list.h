typedef struct List {
  char* val;
  struct List * tail;
} List;

List* list_new(char* x);

char* list_get(List* head, int index);

void list_free(List* lst);
