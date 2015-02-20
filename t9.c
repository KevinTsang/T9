#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "list.h"
#include "trie.h"

void start_interactive_session() {
  char number[MAX_LINE_LENGTH];
  printf("%s", "Enter \"exit\" to quit.\n");
  while (1) {
    printf("%s", "Enter Key Sequence (or \"#\" for next word):\n");
    scanf("%s", number);
    if (strncmp(number, "exit", 4) == 0) {
      break; 
    }
    printf("%s", get_word(number));
  }
}

int main(int argc, char** argv) {
  Trie* trie = (Trie*)malloc(sizeof(Trie));
  if (argc != 1) {
    fputs("Invalid number of arguments", stderr);
    return 1;
  }
  trie_read(trie, argv[1]);
  start_interactive_session();
  trie_free(trie->root);
  free(trie);
  return 0;
}
