#ifndef NET_SOCKET_H
#define NET_SOCKET_H

#include<cstdint>//::std::uint16_t
#include<cstddef>//::std::size_t
#include<string>//::std::string
#include<any>//::std::any

namespace net{

enum class ProtocolFamily{
    INET,
    INET6
};
enum class SocketType{
    STREAM,
    DGRAM
};
enum class Protocol{
    TCP,
    UDP
};
class Socket{
public:
    //库生命周期
    static void start_up(void);
    static void clean_up(void);
    //移动语义
    Socket(Socket&&)noexcept=default;
    Socket& operator=(Socket&&)noexcept=default;
    //禁用复制
    Socket(Socket const&)noexcept=delete;
    Socket& operator=(Socket const&)noexcept=delete;
    //生命周期
    Socket(ProtocolFamily domain,SocketType type,Protocol protocol);
    ~Socket(void)noexcept;
    //服务器端接口
    void bind(::std::string const& ip,::std::uint16_t port);
    void listen(::std::size_t backlog);
    Socket accept(void);
    //客户端接口
    void connect(::std::string const& ip,::std::uint16_t port);
    //工具接口
    bool is_valid(void)noexcept;
    //数据传输
private:
    ::std::any fd_;
    //工具接口用于生成无效的套接字
    Socket(::std::any const& fd)noexcept;
    Socket create_invalid(void)noexcept;
};

}//namespace net

#endif//NET_SOCKET_H
