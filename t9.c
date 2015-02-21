#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "trie.h"

//
void start_interactive_session() {
  char number[MAX_LINE_LENGTH];
  printf("%s", "Enter \"exit\" to quit.\n");
  printf("%s", "Enter Key Sequence (or \"#\" for next word):\n");
  while (fgets(number, MAX_LINE_LENGTH, stdin))
  {
    if (strncmp(number, "exit", 4) == 0  || *number == '\004') {
      return; 
    }
    printf("%s", get_word(number));
    printf("%s", "Enter Key Sequence (or \"#\" for next word):\n");
  }
}

// main function, handles trie population, getting words,
// and freeing memory
int main(int argc, char** argv) {
  Trie* trie = (Trie*)malloc(sizeof(Trie));
  if (argv[1] != NULL) {
    trie_read(trie, argv[1]);
    start_interactive_session();
    trie_free(trie->root);
    free(trie);
    return 0;
  }
  fputs("Invalid number of arguments", stderr);
  return 1;
}
