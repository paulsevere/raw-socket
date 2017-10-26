#ifndef _EV_
#define _EV_ = 0

void removeClient(struct kevent *ke, int client_fd);
void addClient(struct kevent *ke, int client_fd);

#endif  //_EV_