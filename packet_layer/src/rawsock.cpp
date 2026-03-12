#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int create_raw_socket()
{
  int sock = socket(AF_INET, SOCK_RAW,IPPROTO_TCP);
  if(sock < 0)
  {
    perror("socket");
    exit(1);
  }
  
  int one = 1;
  
  if(setsockopt(sock, IPPROTO_IP,IP_HDRINCL, &one, sizeof(one)) < 0)
  {
    perror("setsockopt");
    exit(1);
  }
  
  return sock
}
