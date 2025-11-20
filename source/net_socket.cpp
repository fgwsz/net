#include<net_socket.h>

#include<stdexcept>//::std::runtime_error
#include<unordered_map>//::std::unordered_map

#ifdef _WIN32
    #define NET_WINDOWS 1
#elif defined(__linux__)
    #define NET_LINUX 1
#else
    #define NET_OTHER 1
#endif

#ifdef NET_WINDOWS
    #include<winsock2.h>
#endif

#ifdef NET_LINUX
    #include<sys/socket.h>
#endif

namespace net{

namespace detail{

#ifdef NET_WINDOWS
    static WSADATA wsaData;
#endif

static ::std::unordered_map<::net::ProtocolFamily,int> const to_pf={
    {::net::ProtocolFamily::INET,PF_INET},
    {::net::ProtocolFamily::INET6,PF_INET6}
};
static ::std::unordered_map<::net::Socket,int> const to_sock={
    {::net::SocketType::STREAM,SOCK_STREAM},
    {::net::SocketType::DGRAM,SOCK_DGRAM}
};
static ::std::unordered_map<::net::Socket,int> const to_ip_proto={
    {::net::Protocol::TCP,IPPROTO_TCP},
    {::net::Protocol::UDP,IPPROTO_UDP}
};

#ifdef NET_WINDOWS
    using socket_fd_t=SOCKET;
    #define NET_INVAILD_SOCKET_FD INVAILD_SOCKET
#endif

#ifdef NET_LINUX
    using socket_fd_t=int;
    #define NET_INVAILD_SOCKET_FD (-1)
#endif

inline ::net::detail::sockfd_t& get_socket_fd(::std::any& fd)noexcept{
    return ::std::get<::net::detail::socket_fd_t>(fd);
}

}//namespace net::detail

void Socket::start_up(void){
    #ifdef NET_WINDOWS
        if(WSAStartup(MAKEWORD(2,2),&net::detail::wsaData)!=0){
            throw ::std::runtime_error("Windows:WSAStartup() Error!");
        }
    #endif
}
void Socket::clean_up(void){
    #ifdef NET_WINDOWS
        WSACleanup();
    #endif
}
Socket::Socket(ProtocolFamily domain,SocketType type,Protocol protocol){
    this->fd_=socket(
        ::net::detail::to_pf(domain)
        ,::net::detail::to_sock(type)
        ,::net::detail::to_ip_proto(protocol)
    );
    if(::net::detail::get_socket_fd(this->fd_)==NET_INVAILD_SOCKET_FD){
        throw ::std::runtime_error("Socket::Socket() error!");
    }
}
~Socket(void)noexcept{
    if(this->is_valid){
        #ifdef NET_WINDOWS
            closesocket(::net::detail::get_socket_fd(this->fd_));
        #endif
        #ifdef NET_LINUX
            close(::net::detail::get_socket_fd(this->fd_));
        #endif
    }
}
void Socket::bind(::std::string const& ip,::std::uint16_t port){
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    if(inet_//TODO)
}
void Socket::listen(::std::size_t backlog){
    
}
Socket Socket::accept(void){
    
}
void Socket::connect(::std::string const& ip,::std::uint16_t port){
    
}
bool Socket::is_valid(void)noexcept{
    return this->fd_
}
Socket::Socket(::std::any const& fd)noexcept{
    this->fd_=::net::detail::get_socket_fd(fd);
}
Socket Socket::create_invalid(void)noexcept{
    return Socket(NET_INVAILD_SOCKET_FD);
}

}//namespace net
