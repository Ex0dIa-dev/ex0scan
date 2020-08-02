#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[]) {

  struct sockaddr_in addr;
  int sd, port, init, stop;   // sd = socket, init = first port, stop = last port
  float elapsed;
  time_t start, end;
  time(&start);
  char host[128], service[128];

  init = atoi(argv[2]);
  stop = atoi(argv[3]);

  if (argc < 4) {

    printf("------------------HOW TO USE--------------------\n");
    printf("./ex0scan <IP ADDRESS> <First Port> <Last Port>\n");
    printf("-------------------_by ex0dia_------------------\n");
    exit(1);
  }

  printf("PORT \t STATE \t SERVICE\n");

  for (port = init; port <= stop; port++) {

    //socket creation
    if ((sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) <0 ) {
      printf("Socket Error!\n");
      exit(1);
    }

    memset(&addr, 0, sizeof (addr));

    //socket struct
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(port);

    // connect to port
    if ((connect(sd, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
      printf("");
    } else {
      getnameinfo((struct sockaddr*)&addr, sizeof(addr), host, (sizeof host), service, sizeof(service), 0);
      printf("%d \t open \t %s\n", port, service);
    }
  } // for
  close(sd);

  time(&end);
  elapsed = difftime(end, start);
  printf("Elapsed seconds: %.2f\n", elapsed);

  return 0;
}
