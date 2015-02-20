#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "trie.h"

Trie* trie;
Node* current;
int wordsIndex;

int determineIndex(char c) {
  switch(c) {
    case 'a': case 'b': case 'c': return 0;
    case 'd': case 'e': case 'f': return 1;
    case 'g': case 'h': case 'i': return 2;
    case 'j': case 'k': case 'l': return 3;
    case 'm': case 'n': case 'o': return 4;
    case 'p': case 'q': case 'r': case 's': return 5;
    case 't': case 'u': case 'v': return 6;
    case 'w': case 'x': case 'y': case 'z': return 7;
    default: return -1;
  }
}

void trie_read(Trie* trie_from_main, char* filename) {
  FILE* fp = fopen(filename, "r");
  char buffer[MAX_LINE_LENGTH];
  trie = trie_from_main;
  trie->root = (Node*)malloc(sizeof(Node));
  current = trie->root;
  while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
    for (int i = 0; i < strnlen(buffer, MAX_LINE_LENGTH); i++) {
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
      current->words = list_new(word);
    } else {
      while (currentWord->tail != NULL) {
        currentWord = currentWord->tail;
      }
      currentWord->tail = list_new(word);
    }
    current->totalWords++;
  }
}

char* get_word(char* number) {
  if (number[0] == '#') {
    wordsIndex++;
    if (wordsIndex > current->totalWords) {
      return "There are no more T9nonyms.\n";
    }
    List* currentWord = current->words;
    return list_get(currentWord, wordsIndex);
  } else {
    current = trie->root;
    wordsIndex = 0;
    int size = strnlen(number, MAX_LINE_LENGTH);
    for (int i = 0; i < size; i++) {
      if (number[i] == '#') {
        wordsIndex++;
        if (wordsIndex > current->totalWords) {
          return "There are no more T9nonyms.\n";
        }
      }
      int index = determineIndex(number[i]);
      if (current->next[index] == NULL) {
        return "Not found in current dictionary.\n";
      } else {
        current = current->next[index];
      }
    }
    return list_get(current->words, wordsIndex);
  }
}

void trie_free(Node* root) {
  for (int i = 0; i < 8; i++) {
    if (root->next[i] != NULL) {
      trie_free(root->next[i]);
    }
  }
  list_free(root->words);
  free(root);
}
