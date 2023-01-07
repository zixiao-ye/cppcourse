#include "socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include<cstring>

namespace net{
    bool is_listening(int fd){
        int val;
        socklen_t len = sizeof(val);
        int errn = getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, &val, &len);
        if(val){
            std::cout<<"Success listening!"<<std::endl;
        }
        else{
            std::cout<<"Failure listening!"<<val<<gai_strerror(errn)<<std::endl;
        }
        return val;
    }

    Socket::Socket(){
        fd_ = FileDescriptor(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP));
        int iSetOption = 1;
        setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption));
    }

    void Socket::listen(uint16_t port) const{
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);
        if(bind(fd(), (struct sockaddr *) &addr, sizeof(addr)) == 0){
            std::cout<<"Success bind!"<<std::endl;
        }
        else{
            std::cout<<"Failure bind!"<<errno<<gai_strerror(errno)<<std::endl;
        }
        ::listen(fd(), 5);
    }

    Connection Socket::accept() const{
        if(!is_listening(fd())){
            throw std::runtime_error("The socket is not listening!");
        }
        struct	sockaddr_in fsin;
        socklen_t flen;
        auto sock = ::accept(fd(), (struct sockaddr *)&fsin, &flen);
        FileDescriptor fd{sock};
        return Connection(std::move(fd));
        /* Connection conn{FileDescriptor{sock}};
        return conn; */
    }

    Connection Socket::connect(std::string destination, uint16_t port){
        if (destination == "localhost")
        {
            destination = "127.0.0.1";
        }
        
	    struct addrinfo *host,hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;    /* Allow IPv4*/
        hints.ai_socktype = SOCK_STREAM; 
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        std::string p = std::to_string(port);
	    auto errn = getaddrinfo(destination.c_str(), p.c_str(), &hints, &host);
        if(errn == 0){
            std::cout<<"Success getaddrinfo!"<<p<<std::endl;
        }
        else{
            std::cout<<"Failure getaddrinfo!"<<gai_strerror(errn)<<std::endl;
        }
        if(::connect(fd(), host->ai_addr, host->ai_addrlen) == 0){
            std::cout<<"Success connect!"<<std::endl;
        }
        else{
            std::cout<<"Failure connect!"<<errno<<gai_strerror(errn)<<std::endl;
            throw std::runtime_error("Connect error!");
        }
        return Connection{std::move(fd_)};
    }

    Connection Socket::connect(uint16_t port){
        struct addrinfo *host,hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;    /* Allow IPv4*/
        hints.ai_socktype = SOCK_STREAM; 
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;
        std::string p = std::to_string(port);
        const char* destination = "127.0.0.1";
	    auto errn = getaddrinfo(destination, p.c_str(), &hints, &host);
        if(errn == 0){
            std::cout<<"Success getaddrinfo!"<<p<<std::endl;
        }
        else{
            std::cout<<"Failure getaddrinfo!"<<gai_strerror(errn)<<std::endl;
        }
        if(::connect(fd(), host->ai_addr, host->ai_addrlen) == 0){
            std::cout<<"Success connect!"<<std::endl;
        }
        else{
            std::cout<<"Failure connect!"<<errno<<gai_strerror(errn)<<std::endl;
            throw std::runtime_error("Connect error!");
        }
        return Connection{std::move(fd_)};
    }

    int Socket::fd() const{
        return fd_.unwrap();
    }
}
