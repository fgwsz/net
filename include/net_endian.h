#ifndef NET_ENDIAN_H
#define NET_ENDIAN_H

#include<cstdint>//::std::uint16_t ::std::uint32_t

namespace net{

bool is_big_endian(void)noexcept;
bool is_small_endian(void)noexcept;

::std::uint16_t host_to_net_short(::std::uint16_t host_short)noexcept;
::std::uint16_t net_to_host_short(::std::uint16_t net_short)noexcept;

::std::uint32_t host_to_net_long(::std::uint32_t host_long)noexcept;
::std::uint32_t net_to_host_long(::std::uint32_t net_long)noexcept;

}//namespace net

#endif//NET_ENDIAN_H
