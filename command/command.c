#include <stdio.h>

int handleCommand(char* buf) {
  printf("%s\n", buf);
  return sizeof(buf);
}