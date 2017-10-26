#include <stdlib.h>
#include <sys/event.h>

void removeClient(struct kevent* ke, int client_fd) {
  EV_SET(ke, client_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
};

void addClient(struct kevent* ke, int client_fd) {
  EV_SET(ke, client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
};