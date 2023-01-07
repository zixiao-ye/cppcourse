#include "client.h"
#include <sys/socket.h>

namespace net
{
    Client::Client() : socket{Socket()}{
        /* int iSetOption = 1;
        setsockopt(socket.fd(), SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption)); */
    }

    Connection Client::connect(std::string destination, uint16_t port){
        return socket.connect(destination, port);
    }

    Connection Client::connect(uint16_t port){
        return socket.connect(port);
    }
} // namespace net

