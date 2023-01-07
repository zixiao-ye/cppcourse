#include "server.h"
#include <sys/socket.h>

namespace net
{
    Server::Server(uint16_t port){
        /* int iSetOption = 1;
        setsockopt(socket.fd(), SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption)); */
        socket.listen(port);
    }

    Connection Server::accept(){
        return socket.accept();
    }
} // namespace net
