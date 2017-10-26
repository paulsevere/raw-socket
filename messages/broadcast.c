#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../util/users.h"

int broadcast(char* msg, int sender_fd) {
  int n;
  int outcome;
  for (n = 0; n < NUSERS; n++) {
    int cli_fd = users[n].uc_fd;
    if (cli_fd != sender_fd && cli_fd != 0) {
      outcome = write(cli_fd, msg, sizeof(msg));
      if (outcome != sizeof(msg)) err(1, "Error broadcasting");
    }
  }
  return 1;
}