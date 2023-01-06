#include "socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

namespace net{
    bool is_listening(int fd){
        int val;
        socklen_t len = sizeof(val);
        int errn = getsockopt(fd, SOL_SOCKET, SO_ACCEPTCONN, NULL, 0);
        if(errn == 0){
            std::cout<<"Success listening!"<<std::endl;
        }
        else if(errn == -1){
            std::cout<<"Failure listening!"<<gai_strerror(errn)<<std::endl;
        }
        return errn == 0;
    }

    Socket::Socket(){
        fd_ = FileDescriptor(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP));
    }

    void Socket::listen(uint16_t port) const{
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);
        if(bind(fd(), (struct sockaddr *) &addr, sizeof(addr)) == 0){
            // std::cout<<"Success!"<<std::endl;
        }
        else{
            // std::cout<<"Failure!"<<errno<<std::endl;
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
        Connection conn(FileDescriptor{sock});
        return conn;
    }

    Connection Socket::connect(std::string destination, uint16_t port){
        struct addrinfo *host;
        if (destination == "localhost")
        {
            destination = "127.0.0.1";
        }
        
	    getaddrinfo((char*)&destination, (char*)&port, NULL, &host);
        ::connect(fd(), host->ai_addr, host->ai_addrlen);
        return Connection{std::move(fd_)};
    }

    Connection Socket::connect(uint16_t port){
        struct addrinfo *host;
        std::string p = std::to_string(port);
	    auto errn = getaddrinfo("127.0.0.1", (char*)&p, NULL, &host);
        if(errn == 0){
            // std::cout<<"Success!"<<p<<std::endl;
        }
        else{
            // std::cout<<"Failure!"<<gai_strerror(errn)<<std::endl;
        }
        if(::connect(fd(), host->ai_addr, host->ai_addrlen) == 0){
            std::cout<<"Success connect!"<<std::endl;
        }
        else{
            std::cout<<"Failure connect!"<<errno<<gai_strerror(errn)<<std::endl;
        }
        return Connection{std::move(fd_)};
    }

    int Socket::fd() const{
        return fd_.unwrap();
    }
}
