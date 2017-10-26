#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../util/users.h"

int isConnectedSocket(int ke_ident) {
  printf("RUNNING FOMR OTHER FILE\n");
  int i;
  for (i = 0; i < NUSERS; i++) {
    if (users[i].uc_fd == ke_ident) {
      break;
    }
  }
  return i;
}
