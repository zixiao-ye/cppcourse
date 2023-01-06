#pragma once

#include "filedescriptor.h"
#include <istream>
#include <span>
#include <string_view>

namespace net {
/// Light wrapper around the libc send(3)-function. Should return the value returned by send(3), and
/// the options should be set to 0.
[[nodiscard]] ssize_t send(int fd, std::span<const char> data);

/// Light wrapper around libc recv(3)-function. Should return the value returned by recv(3), and the
/// options should be set to 0;
[[nodiscard]] ssize_t receive(int fd, std::span<char> buf);

/// One endpoint of a TCP connection. It can send and receive data from and to the other end of the
/// endpoint.
/// 
/// HINT: If the compiler complains that it can't find the correct function. Try prefixing it with
/// `::` to call the global version, not the class variant.
class Connection {
public:
    /// Take ownership of a file descriptor
    Connection(FileDescriptor&& fd);

    /// Send data from a string_view to the given file descriptor.
    ///
    /// Check out: send(3)
    void send(std::string_view data) const;

    /// Send data from an `std::istream` to the given file descriptor
    /// Check out: send(3)
    void send(std::istream& data) const;

    /// Receive data from the underlying socket, and write it to the `std::ostream`. Importantly,
    /// just read a chunk of data, write it to the stream and finish the function. Use 128
    /// bytes/chars for the buffer size. If you want to ensure that you read all data from the
    /// socket, use `receive_all`.
    ///
    /// Return the size read from the socket.
    ///
    /// Check out: recv(3)
    [[nodiscard]] ssize_t receive(std::ostream& stream) const;

    /// Receive all data from the socket. This continuously reads a chunk from the socket and
    /// concatenates it to the stream. It reads until no data is more available (hint hint, see the
    /// man pages).
    ///
    /// Return the size read from the socket.
    ///
    /// Check out: recv(3)
    [[maybe_unused]] ssize_t receive_all(std::ostream& stream) const;

    /// Return the underlying file descriptor
    int fd() const;

public:
    FileDescriptor fd_;
};

} // namespace net
