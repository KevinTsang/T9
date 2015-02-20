#define MAX_LINE_LENGTH 100

typedef struct Node {
  List* words;
  struct Node* next[8];
  int totalWords;
} Node;

typedef struct Trie {
  Node* root;
} Trie;

void trie_read(Trie* trie_from_main, char* filename);

char* get_word(char* number);

void trie_free(Node* root);
