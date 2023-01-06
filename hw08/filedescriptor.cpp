#include "filedescriptor.h"
#include <unistd.h>

namespace net{
    FileDescriptor::FileDescriptor(){
        fd_ = -1;
    }
    FileDescriptor::FileDescriptor(int fd){
        fd_ = fd;
    }

    FileDescriptor::~FileDescriptor(){
        close(fd_.value());
    }

    FileDescriptor::FileDescriptor(FileDescriptor&& fd) : fd_{fd.fd_} {
        fd.fd_ = -1;
    }
    
    FileDescriptor& FileDescriptor::operator=(FileDescriptor&& fd){
        std::swap(fd_, fd.fd_);
        return *this;
    }

    int FileDescriptor::unwrap() const{
        return fd_.value();
    }
}

