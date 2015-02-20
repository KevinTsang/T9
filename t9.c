#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void startInteractiveSession() {
  char number[MAX_LINE_LENGTH];
  printf("%s", "Enter \"exit\" to quit.\n");
  while (1) {
    printf("%s", "Enter Key Sequence (or \"#\" for next word):\n");
    scanf("%s", number);
    if (strncmp(number, "exit", 4) != 0) {
      printf("%s", getWord(number));
    } else {
      freeTrie(trie->root);
      break;
    }
  }
}

int main(int argc, char** argv) {
  wordsIndex = 0;
  trie = (Trie*)malloc(sizeof(Trie));
  readIntoTrie(argv[1]);
  startInteractiveSession();
  return 0;
}
