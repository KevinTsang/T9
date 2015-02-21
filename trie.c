/**
 * Kevin Tsang
 * CSE 374
 * 2/20/2015
 * A trie implementation which stores and retrieves
 * words based on number input.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "trie.h"

Trie* trie;
Node* current;
int wordsIndex;

// determines what index is associated with a T9
// letter input based on a character
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

// takes a trie and a char* representing a filename
// populates the trie using each line within the given
// file name
void trie_read(Trie* trie_from_main, char* filename) {
  FILE* fp = fopen(filename, "r");
  char buffer[MAX_LINE_LENGTH];
  trie = trie_from_main;
  trie->root = (Node*)calloc(1, sizeof(Node));
  Node* node = trie->root;
  while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
    for (int i = 0; i < strlen(buffer); i++) {
      if (buffer[i] == '\n') {
        break;
      }
      int index = determineIndex(buffer[i]);
      if (node->next[index] == NULL) {
        Node* new = (Node*)calloc(1, sizeof(Node));
	node->next[index] = new;
	node->totalWords = 0;
      }
      node = node->next[index];
    }
    int size = strlen(buffer);
    char* word = (char*)calloc(size, sizeof(char));
    strncpy(word, buffer, size);
    List* currentWord = node->words;
    if (currentWord == NULL) {
      node->words = list_new(word);
    } else {
      while (currentWord->tail != NULL) {
        currentWord = currentWord->tail;
      }
      currentWord->tail = list_new(word);
    }
    node->totalWords++;
    node = trie->root;
  }
  current = trie->root;
}

// takes a number as a character array
// traverses a trie and returns a number
// associated with that key combination
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
    int size = strlen(number);
    for (int i = 0; i < size - 1; i++) { 
    // the minus 1 is there to handle the extra newline that gets added in
      if (number[i] == '#') {
        wordsIndex++;
      } else {
        int index = number[i] - '0' - 2; 
        if (current->next[index] == NULL) {
          return "Not found in current dictionary.\n";
        } else {
          current = current->next[index];
        }
      }
    }
    if (wordsIndex > current->totalWords) {
      return "There are no more T9nonyms.\n";
    } else {
      List* currentWord = current->words;
      return list_get(currentWord, wordsIndex);
    }
  }
}

// takes in the root node of a trie
// frees up any allocated memory it used
void trie_free(Node* root) {
  for (int i = 0; i < 8; i++) {
    if (root->next[i] != NULL) {
      trie_free(root->next[i]);
    }
  }
  list_free(root->words);
  free(root);
}
