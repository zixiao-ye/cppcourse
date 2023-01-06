#pragma once

#include "connection.h"
#include "filedescriptor.h"

namespace net {

/// Return true, if the given file descriptor is listening.
/// Use getsockopt(3), retrieve options for the socket level, and the option is `SO_ACCEPTCONN`. If
/// you are unsure, read the man pages :-)
bool is_listening(int fd);

/// A Linux Socket. Sockets are communication end points, in our case there are TCP endpoints. In
/// Linux as pretty much everything, they are represented by a file descriptor.
///
/// See also socket(7)
class Socket {
public:
    /// Initialize the TCP socket for IPv4. The type should be `SOCK_STREAM`. Check out socket(2)
    /// and ip(7).
    Socket();

    /// You should not need to implement a destructor
    ~Socket() = default;

    /// Bind and then listen on the given port. Listen on any incoming address. Be sure to use the
    /// correct endianness for the port.
    ///
    /// Check out bind(3), ip(7) and listen(2), htons(3)
    void listen(uint16_t port) const;

    /// Wait for a connection to appear, and then return the newly created connection. Check that
    /// the socket is already listening, throw an instance of `std::runtime_error` if the socket is
    /// not listening. The returned connection shall take ownership to close the new socket file
    /// descriptor.
    ///
    /// Check out accept(3)
    Connection accept() const;

    /// Connect to the destination on the given port (be sure of endianness!). `destination` can
    /// either be an IPv4 address of the form "8.8.8.8" or "127.0.0.1", but also accept "localhost"
    /// and convert that to the correct IPv4 address.
    ///
    /// The connection is one shot, i.e. after the connection is closed, the socket should be closed
    /// as well. The responsibility is transferred to the Connection.
    ///
    /// Check out: inet_addr(3), connect(3), gethostbyname(3), htons(3)
    Connection connect(std::string destination, uint16_t port);

    /// Connect to localhost on the given port, see the other overload
    Connection connect(uint16_t port);

    /// Return the int to the file descriptor
    int fd() const;

private:
    FileDescriptor fd_;
};

} // namespace net
