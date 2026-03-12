#include "../include/ip_header.hpp"
#include "../include/tcp_header.hpp"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
  
  if(sock < 0)
  {
    perror("socket");
    return 1;
  }
  
  int one = 1;
  setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one));
  
  char packet[4096];
  memset(packet, 0, 4096);
  
  IPHeader *ip = (IPHeader*)packet;
  TCPHeader *tcp = (TCPHeader*)(packet + sizeof(IPHeader));
  
  ip->ihl = 5;
  ip->version = 4;
  ip->ttl = 64;
  ip->protocol = IPPROTO_TCP;
  
  ip->saddr = inet_addr("127.0.0.1");
  ip->daddr = inet_addr("127.0.0.1");
  
  tcp->source = htons(50000);
  tcp->dest = htons(8080);
  
  tcp->seq = htonl(1000);
  tcp->syn = 1;
  tcp->doff = 5;
  tcp->window = htons(65535);
  
  sockaddr_in dest;
  
  dest.sin_family = AF_INET;
  dest.sin_port = tcp->dest;
  dest.sin_addr.s_addr = ip->daddr;
  
  sendto(sock, packet, sizeof(IPHeader) + sizeof(TCPHeader),0,(sockaddr*)&dest, sizeof(dest));
  
  std::cout << "SYN sent\n";
  
  char buffer[65536];
  
  while(true)
  {
    int len = recv(sock, buffer, sizeof(buffer), 0);
    IPHeader *rip = (IPHeader*)buffer;
    TCPHeader *rtcp = (TCPHeader*)(buffer + rip->ihl*4);
    
    if(rtcp->syn && rtcp->ack)
    {
      std::cout << "SYN-ACK received\n";
      break;
    }
  }
  
  tcp->syn = 0;
  tcp->ack = 1;
  
  sendto(sock, packet, sizeof(IPHeader) + sizeof(TCPHeader), 0, (sockaddr*)&dest,sizeof(dest));
  
  std::cout << "Ack sent\n";
}
