#pragma once

using ssize_t=long long;

class Buffer{
};

class Socket;
class SockAddr{
    int bind_to(Socket& sock)const;
    int accept_from_tcp(Socket& sock);
};

class Socket{
public:
    Socket(Socket const&)=default;
    Socket& operator=(Socket const&)=default;

    Socket(int domanin,int type,int protocol);
    explicit Socket(int fd);
    ~Socket(void);
    int bind(SockAddr const& addr);
    int tcp_listen(int backlog);
    Socket tcp_accept(SockAddr& addr);
    ssize_t write(Buffer const& buf);
    ssize_t read(Buffer const& buf);
    bool empty(void);
private:
    int fd_;
}
Socket::Socket(int domanin,int type,int protocol){
    this->fd_=socket(domanin,type,protocol);
}
bool Socket::empty(void){
    return this->fd_==-1;
}
int Socket::bind(SockAddr& addr){
    if(this->empty()){
        return -1;
    }
    return addr.bind_to(*this);
}
int Socket::tcp_listen(int backlog){
    if(this->empty()){
        return -1;
    }
    return listen(this->fd_,backlog);
}
Socket Socket::tcp_accept(SockAddr& addr){
    if(this->empty()){
        return -1;
    }
    return Socket(addr.accept_from_tcp(*this));
}
