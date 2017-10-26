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
#include "./connections/handleConnection.h"
#include "./ev/ev.h"
#include "./hash/hash.h"
#include "./messages/broadcast.h"
#include "./messages/handleMessage.h"
#include "./util/color.h"
#include "./util/users.h"
#include "./util/util.h"

int main(int argc, char **argv) {
  printf("%f\n", atof(argv[1]));
  return 0;
}