/**
 * Kevin Tsang
 * CSE 374
 * 2/20/2015
 * Trie header file*/

// max length of a word stored in a trie
// as well as max number of characters for 
// getting a T9 word out of the trie
#define MAX_LINE_LENGTH 100

// a single node that comprises part of the trie
typedef struct Node {
  List* words;
  struct Node* next[8];
  int totalWords;
} Node;

// the actual trie structure itself
typedef struct Trie {
  Node* root;
} Trie;

// takes a trie and a char* representing a filename
// populates the trie using each line within the given
// file name
void trie_read(Trie* trie_from_main, char* filename);

// takes a number as a character array
// traverses a trie and returns a number
// associated with that key combination
char* get_word(char* number);

// takes in the root node of a trie
// frees up any allocated memory it used
void trie_free(Node* root);
