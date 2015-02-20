#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Node {
  List* words;
  struct Node* next[8];
  int totalWords;
} Node;

typedef struct Trie {
  Node* root;
} Trie;

Trie* trie;
Node* current;
int wordsIndex;

int determineIndex(char c) {
  if (c == 'a' || c == 'b' || c == 'c') {
    return 0;
  } else if (c == 'd' || c == 'e' || c == 'f') {
    return 1;
  } else if (c == 'g' || c == 'h' || c == 'i') {
    return 2;
  } else if (c == 'j' || c == 'k' || c == 'l') {
    return 3;
  } else if (c == 'm' || c == 'n' || c == 'o') {
    return 4;
  } else if (c == 'p' || c == 'q' || c == 'r' || c == 's') {
    return 5;
  } else if (c == 't' || c == 'u' || c == 'v') {
    return 6;
  } else if (c == 'w' || c == 'x' || c == 'y' || c == 'z') {
    return 7;
  } else { // not found case
    return -1;
  }
}

void readIntoTrie(char* filename) {
  FILE* fp = fopen(filename, "r");
  char buffer[MAX_LINE_LENGTH];
  trie->root = (Node*)malloc(sizeof(Node));
  current = trie->root;
  while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
    int i = 0;
    for (; i < strnlen(buffer, MAX_LINE_LENGTH); i++) {
      if (buffer[i] == '\n') {
        break;
      }
      int index = determineIndex(buffer[i]);
      if (current->next[index] == NULL) {
        Node* new = (Node*)malloc(sizeof(Node));
	current->next[index] = new;
	current->totalWords = 0;
      }
      current = current->next[index];
    }
    int size = strnlen(buffer, MAX_LINE_LENGTH);
    char* word = (char*)malloc(sizeof(char)*size);
    strncpy(word, buffer, MAX_LINE_LENGTH);
    List* currentWord = current->words;
    if (currentWord == NULL) {
      current->words = createNewNode(word);
    } else {
      while (currentWord->tail != NULL) {
        currentWord = currentWord->tail;
      }
      currentWord->tail = createNewNode(word);
    }
    current->totalWords++;
  }
}

char* getWord(char* number) {
  if (number[0] == '#') {
    wordsIndex++;
    if (wordsIndex > current->totalWords) {
      return "There are no more T9nonyms.\n";
    }
    int i = 0;
    List* currentWord = current->words;
    return get(currentWord, wordsIndex);
  } else {
    current = trie->root;
    wordsIndex = 0;
    int i = 0;
    int size = strnlen(number, MAX_LINE_LENGTH);
    for (; i < size; i++) {
      if (number[i] == '#') {
        wordsIndex++;
        if (wordsIndex > current->totalWords) {
          return "There are no more T9nonyms.\n";
        }
      }
      int index = determineIndex(number[i]);
      if (current[index] == NULL) {
        return "Not found in current dictionary.\n";
      } else {
        current = current->[index];
      }
    }
    return get(current->words, wordsIndex);
  }
}

void freeTrie(Node* root) {
  int i = 0;
  for (; i < 8; i++) {
    if (root->next[i] != NULL) {
      freeTrie(root->next[i]);
      free(root->next[i]);
    }
  }
  free_list(root->words);
  free(root);
}
