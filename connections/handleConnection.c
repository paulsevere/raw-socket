#include <arpa/inet.h>
#include <err.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "../util/users.h"

int handleConnection(int servsock, int kq, struct kevent ke, int uidx) {
  struct sockaddr_in c; /* client */
  socklen_t len = (socklen_t)sizeof(c);
  char *umsg = "too many users!\n";

  int i = accept(servsock, (struct sockaddr *)&c, &len);
  if (i == -1) err(1, "accept!");

  for (uidx = 0; uidx < NUSERS; uidx++)
    if (users[uidx].uc_fd == 0) break;

  if (uidx == NUSERS) {
    warnx("%s", umsg);
    write(i, umsg, strlen(umsg));
    close(i);
    return -1;
  }

  users[uidx].uc_fd = i; /* users file descriptor */
  users[uidx].uc_addr = strdup(inet_ntoa(c.sin_addr));
  printf("USER ADDR:  %d\n", users[uidx].uc_fd);
  if (users[uidx].uc_addr == NULL) err(1, "strdup");

  EV_SET(&ke, i, EVFILT_READ, EV_ADD, 0, 0, NULL);
  i = kevent(kq, &ke, 1, NULL, 0, NULL);
  if (i == -1) err(1, "kevent add user!");

  printf("user on fd %d added\n", users[uidx].uc_fd);
  return 0;
}