#ifndef NET_ENDIAN_H
#define NET_ENDIAN_H

#include<cstdint>//uint16_t uint32_t

namespace net{

bool is_big_endian(void)noexcept;
bool is_small_endian(void)noexcept;

uint16_t host_to_net_short(uint16_t host_short)noexcept;
uint16_t net_to_host_short(uint16_t net_short)noexcept;

uint32_t host_to_net_long(uint32_t host_long)noexcept;
uint32_t net_to_host_long(uint32_t net_long)noexcept;

}//namespace net

#endif//NET_ENDIAN_H
