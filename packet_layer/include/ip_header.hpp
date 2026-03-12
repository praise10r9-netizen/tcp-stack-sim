#ifndef IP_HEADER_HPP
#define IP_HEADER_HPP

#include <stdint.h>

struct IPHeader
{
  uint8_t ihl:4;
  uint8_t version:4;
  
  uint8_t tos;
  uint16_t tot_len;
  
  uint16_t id;
  uint16_t frag_off;
  
  uint8_t ttl;
  uint8_t protocol;
  
  uint16_t check;
  
  uint32_t saddr;
  uint32_t daddr;
};

#endif
