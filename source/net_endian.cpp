#include<net_endian.h>

#include<cstdint>//::std::uint8_t ::std::uint16_t ::std::uint32_t

namespace net{

bool is_big_endian(void)noexcept{
    union{
        ::std::uint8_t data_[4];
        ::std::uint32_t number_;
    }test;
    test.number_=0x01020304;
    return test.data_[0]==0x01;
}

bool is_small_endian(void)noexcept{
    return !::net::is_big_endian();
}

namespace detail{

inline ::std::uint16_t endian_swap_short(::std::uint16_t number)noexcept{
    union{
        ::std::uint8_t data_[2];
        ::std::uint16_t number_;
    }result;
    result.number_=number;
    ::std::uint8_t temp=result.data_[0];
    result.data_[0]=result.data_[1];
    result.data_[1]=temp;
    return result.number_;
}

inline ::std::uint32_t endian_swap_long(::std::uint32_t number)noexcept{
    union{
        ::std::uint8_t data_[4];
        ::std::uint32_t number_;
    }result;
    result.number_=number;
    ::std::uint8_t temp=result.data_[0];
    result.data_[0]=result.data_[3];
    result.data_[3]=temp;
    temp=result.data_[1];
    result.data_[1]=result.data_[2];
    result.data_[2]=temp;
    return result.number_;
}

}//namespace net::detail

::std::uint16_t host_to_net_short(::std::uint16_t host_short)noexcept{
    if(::net::is_big_endian()){
        return host_short;
    }
    return ::net::detail::endian_swap_short(host_short);
}
::std::uint16_t net_to_host_short(::std::uint16_t net_short)noexcept{
    if(::net::is_big_endian()){
        return net_short;
    }
    return ::net::detail::endian_swap_short(net_short);
}

::std::uint32_t host_to_net_long(::std::uint32_t host_long)noexcept{
    if(::net::is_big_endian()){
        return host_long;
    }
    return ::net::detail::endian_swap_long(host_long);
}
::std::uint32_t net_to_host_long(::std::uint32_t net_long)noexcept{
    if(::net::is_big_endian()){
        return net_long;
    }
    return ::net::detail::endian_swap_long(net_long);
}

}//namespace net
