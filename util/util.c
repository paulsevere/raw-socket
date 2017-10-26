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

int mksock(char *addr, int port) {
  int i, sock;
  struct sockaddr_in serv;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) err(1, "socket");

  i = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&i,
                 (socklen_t)sizeof(i)) == -1)
    warn("setsockopt");

  memset(&serv, 0, sizeof(struct sockaddr_in));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(port);
  serv.sin_addr.s_addr = inet_addr(addr);

  i = bind(sock, (struct sockaddr *)&serv, (socklen_t)sizeof(serv));
  if (i == -1) err(1, "bind");

  i = listen(sock, 5);
  if (i == -1) err(1, "listen");
  return (sock);
}