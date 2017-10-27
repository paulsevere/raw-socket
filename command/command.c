#include <stdio.h>
#include <string.h>
#include "../hash/hash.h"

int matchCommands(char* command) {
  if (strcmp(command, "get") == 0) {
    return 1;
  } else if (strcmp("set", command) == 0) {
    return 2;
  } else {
    return 0;
  }
}

int handleCommand(char* buf, hashtable_t* hashtable) {
  char* token;
  int tok_count;
  token = strtok(buf, "  \n");
  printf("COMMAND: %s\n", token);
  switch (matchCommands(token)) {
    case 1:
      printf("get command\n");
      break;
    case 2:
      printf("set command \n");
      break;
    default:
      printf("NO MATCH\n");
  }

  while (token != NULL) {
    token = strtok(NULL, " ");
    tok_count++;
  }
  // ht_set(hashtable, "COOL", "OK");
  return tok_count;
}