#pragma once

#include<iostream>//::std::cout
#include<vnitest/vnitest.h>
#include<net_endian.h>

VNITEST_CASE("net_endian.is_big_endian"){
    union{
        uint8_t data_[2];
        uint16_t number_;
    }test;
    test.data_[0]=0x01;
    test.data_[1]=0x02;
    VNITEST_RUNTIME_CHECK_EQ((test.number_==0x0102),::net::is_big_endian());
}

VNITEST_CASE("net_endian.is_small_endian"){
    union{
        uint8_t data_[2];
        uint16_t number_;
    }test;
    test.data_[0]=0x01;
    test.data_[1]=0x02;
    VNITEST_RUNTIME_CHECK_EQ((test.number_==0x0201),::net::is_small_endian());
}

VNITEST_CASE("net_endian.host_to_net_short"){
    uint16_t host_short=0x0102;
    uint16_t net_short;
    if(::net::is_big_endian()){
        net_short=0x0102;
    }else{
        net_short=0x0201;
    }
    VNITEST_RUNTIME_CHECK_EQ(net_short,::net::host_to_net_short(host_short));
}

VNITEST_CASE("net_endian.net_to_host_short"){
    uint16_t net_short=0x0102;
    uint16_t host_short;
    if(::net::is_big_endian()){
        host_short=0x0102;
    }else{
        host_short=0x0201;
    }
    VNITEST_RUNTIME_CHECK_EQ(host_short,::net::net_to_host_short(net_short));
}

VNITEST_CASE("net_endian.host_to_net_long"){
    uint32_t host_long=0x01020304;
    uint32_t net_long;
    if(::net::is_big_endian()){
        net_long=0x01020304;
    }else{
        net_long=0x04030201;
    }
    VNITEST_RUNTIME_CHECK_EQ(net_long,::net::host_to_net_long(host_long));
}

VNITEST_CASE("net_endian.net_to_host_long"){
    uint32_t net_long=0x01020304;
    uint32_t host_long;
    if(::net::is_big_endian()){
        host_long=0x01020304;
    }else{
        host_long=0x04030201;
    }
    VNITEST_RUNTIME_CHECK_EQ(host_long,::net::net_to_host_long(net_long));
}

VNITEST_GROUP("net_endian"){
    VNITEST_GROUP_ELEMENT_CASE_REGEX(R"(^net_endian.*)");
}

void test_net_endian(void){
    ::std::cout<<::vnitest::execute_group_to_json("net_endian")<<'\n';
}
