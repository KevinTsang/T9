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

#include "trie.h"

Trie* trie;
Node* current;

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
    case '#': return 8;
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
      }
      node = node->next[index];
    }
    int size = strlen(buffer) + 1;
    char* word = (char*)calloc(size, sizeof(char));
    strncpy(word, buffer, size);
    if (node->word == NULL) {
      node->word = word;
    } else {
      while (node->next[8] != NULL) {
        node = node->next[8];
      }
      Node* new = (Node*)calloc(1, sizeof(Node));
      node->next[8] = new;
      new->word = word;
    }
    node = trie->root;
  }
  current = trie->root;
  fclose(fp);
}

// takes a number as a character array
// traverses a trie and returns a number
// associated with that key combination
char* get_word(char* number) {
  if (number[0] == '#') {
    if (current->next[8] == NULL) {
      return "There are no more T9nonyms.\n";
    }
    current = current->next[8];
    return current->word;
  } else {
    current = trie->root;
    int size = strlen(number) - 1;
    for (int i = 0; i < size; i++) { 
    // the minus 1 is there to handle the extra newline that gets added in
      if (number[i] == '#') {

        current = current->next[8];
        if (current == NULL && i < size) {
          break; // handles if they have a # in the middle of their number
        }
      } else {
        int index = number[i] - '0' - 2; 
        if (current->next[index] == NULL) {
          return "Not found in current dictionary.\n";
        } else {
          current = current->next[index];
        }
      }
    }
    if (current == NULL) {
      return "There are no more T9nonyms.\n";
    } else if (current->word == NULL) {
      return "Not found in current dictionary.\n";
    } else {
      return current->word;
    }
  }
}

// takes in the root node of a trie
// frees up any allocated memory it used
void trie_free(Node* root) {
  for (int i = 0; i < 9; i++) {
    if (root->next[i] != NULL) {
      trie_free(root->next[i]);
    }
  }
  free(root->word);
  free(root);
}
