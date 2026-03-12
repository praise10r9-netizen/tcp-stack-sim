#ifndef TCP_HEADER_HPP
#define TCP_HEADER_HPP

#include <stdint.h>

struct TCPHeader
{
  uint16_t source;
  uint16_t dest;
  
  uint32_t seq;
  uint32_t ack_seq;
  
  uint16_t res1:4;
  uint16_t doff:4;
  
  uint16_t fin:1;
  uint16_t syn:1;
  uint16_t rst:1;
  uint16_t psh:1;
  uint16_t ack:1;
  uint16_t urg:1;
  
  uint16_t res2:2;
  
  uint16_t window;
  uint16_t check;
  uint16_t urg_ptr;
};

#endif
