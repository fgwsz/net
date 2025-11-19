#include<net_endian.h>

#include<cstdint>//uint8_t uint16_t uint32_t

namespace net{

constexpr bool is_big_endian(void)noexcept{
    union{
        uint8_t data_[4];
        uint32_t number_;
    }test={0x01020304};
    return test.data_[0]==0x01;
}

constexpr bool is_small_endian(void)noexcept{
    return !::net::is_big_endian();
}
namespace detail{

inline uint16_t endian_swap_short(uint16_t number)noexcept{
    union{
        uint8_t data_[2];
        uint16_t number_;
    }result=number;
    uint8_t temp=result.data_[0];
    result.data_[0]=result.data_[1];
    result.data_[1]=temp;
    return result.number_;
}

inline uint32_t endian_swap_long(uint32_t number)noexcept{
    union{
        uint8_t data_[4];
        uint32_t number_;
    }result=number;
    uint8_t temp=result.data_[0];
    result.data_[0]=result.data_[3];
    result.data_[3]=temp;
    temp=result.data_[1];
    result.data_[1]=result.data_[2];
    result.data_[2]=temp;
    return result.number_;
}

}//namespace net::detail

uint16_t host_to_net_short(uint16_t host_short)noexcept{
    if constexpr(::net::is_big_endian()){
        return host_short;
    }
    return ::net::detail::endian_swap_short(host_short);
}
uint16_t net_to_host_short(uint16_t net_short)noexcept{
    if constexpr(::net::is_big_endian()){
        return net_short;
    }
    return ::net::detail::endian_swap_short(net_short);
}

uint32_t host_to_net_long(uint32_t host_long)noexcept{
    if constexpr(::net::is_big_endian()){
        return host_long;
    }
    return ::net::detail::endian_swap_long(host_long);
}
uint32_t net_to_host_long(uint32_t net_long)noexcept{
    if constexpr(::net::is_big_endian()){
        return net_long;
    }
    return ::net::detail::endian_swap_long(net_long);
}

}//namespace net
