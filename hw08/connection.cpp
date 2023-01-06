#include "connection.h"
#include <sys/socket.h>

#define BUFLEN (20 << 20)

namespace net{
    ssize_t send(int fd, std::span<const char> data){
        return ::send(fd, data.data(), data.size_bytes(), 0);
    }

    ssize_t receive(int fd, std::span<char> buf){
        return recv(fd, buf.data(), buf.size_bytes(), 0);
    }

    Connection::Connection(FileDescriptor&& fd){
        fd_ = std::move(fd);
    }

    void Connection::send(std::string_view data) const{
        ::send(fd(), data.data(), data.size(), 0);
    }

    void Connection::send(std::istream& data) const{
        data.seekg (0, data.end);
        auto length = data.tellg();
        data.seekg (0, data.beg);

        char * buf = new char [size_t(length)];
        data.read (buf,length);
        ::send(fd(), buf, size_t(length), 0);
        delete[] buf;
    }

    ssize_t Connection::receive(std::ostream& stream) const{
        char *buf=(char *)malloc(BUFLEN);
        auto len = recv(fd(), buf, BUFLEN, 0);
        stream<<buf;
        free(buf);
        return len;
    }

    ssize_t Connection::receive_all(std::ostream& stream) const{
        char *buf=(char *)malloc(BUFLEN);
        auto len = recv(fd(), buf, BUFLEN, MSG_WAITALL);
        stream<<buf;
        free(buf);
        return len;
    }

    int Connection::fd() const{
        return fd_.unwrap();
    }

}