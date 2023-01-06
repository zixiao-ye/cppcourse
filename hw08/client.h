#pragma once

#include "connection.h"
#include "socket.h"

namespace net {

/**
 * TCP socket client. Can connect to a server given a destination IP address and a port.
 */
class Client {
public:
    Client();

    Connection connect(std::string destination, uint16_t port);

    Connection connect(uint16_t port);
private:
    Socket socket;
};

} // namespace net
