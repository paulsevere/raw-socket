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
#include "./command/command.h"
#include "./connections/handleConnection.h"
#include "./ev/ev.h"
#include "./hash/hash.h"
#include "./messages/broadcast.h"
#include "./messages/handleMessage.h"
#include "./util/color.h"
#include "./util/users.h"
#include "./util/util.h"

hashtable_t* hashtable;

int main(void) {
  hashtable = ht_create(1024);

  int servsock, kq, i, uidx;
  struct kevent ke;
  struct sockaddr_in c; /* client */
  socklen_t len;
  char buf[1024];
  void* patrick = "patrick";
  ht_set(hashtable, "first", patrick);
  int cool = 10;
  void* ten = malloc(sizeof(10));
  ten = &cool;

  ht_set(hashtable, "ten", ten);

  printf("%s\n", ht_get(hashtable, "first"));
  printf("%s\n", ht_get(hashtable, "ten"));

  servsock = mksock("127.0.0.1", 3000);

  kq = kqueue();
  if (kq == -1) err(1, "kqueue!");

  memset(&ke, 0, sizeof(struct kevent));
  memset(users, 0, sizeof(struct uc) * NUSERS);

  EV_SET(&ke, servsock, EVFILT_READ, EV_ADD, 0, 5, NULL);

  i = kevent(kq, &ke, 1, NULL, 0, NULL);
  if (i == -1) err(1, "set kevent");

  while (1) {
    memset(&ke, 0, sizeof(ke));

    i = kevent(kq, NULL, 0, &ke, 1, NULL);

    if (i == -1) err(1, "kevent!");

    if (i == 0) continue;

    if (ke.ident == servsock)
      handleConnection(servsock, kq, ke, uidx);
    else {
      uidx = isConnectedSocket(ke.ident);

      if (uidx == NUSERS) errx(1, "bogus message!");

      memset(buf, 0, sizeof(buf));

      i = read(users[uidx].uc_fd, buf, sizeof(buf));

      handleCommand(buf);

      if (i == -1) continue;

      if (i == 0) { /* EOF from a client */

        printf("removing %d\n", users[uidx].uc_fd);

        removeClient(&ke, users[uidx].uc_fd);
        // EV_SET(&ke, users[uidx].uc_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);

        i = kevent(kq, &ke, 1, 0, 0, NULL);
        if (i == -1) err(1, "rm user from kq");

        close(users[uidx].uc_fd);
        free(users[uidx].uc_addr);

        users[uidx].uc_fd = 0;
        users[uidx].uc_addr = NULL;

        continue;
      }

      log_blue("got a message from ");
      printf("%d\n", users[uidx].uc_fd);

      /* now write it to the other users */
      broadcast(buf, users[uidx].uc_fd);
      // for (uidx = 0; uidx < NUSERS; uidx++) {
      //   if (users[uidx].uc_fd == 0 || users[uidx].uc_fd == ke.ident)
      //   continue;

      //   i = write(users[uidx].uc_fd, buf, sizeof(buf));
      //   if (i == -1) warn("write failed!");
      // }
    } /* end if */
  }   /* end while */

  return (0);
}
