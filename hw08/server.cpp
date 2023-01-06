#include "server.h"

namespace net
{
    Server::Server(uint16_t port){
        socket.listen(port);
    }

    Connection Server::accept(){
        return socket.accept();
    }
} // namespace net
