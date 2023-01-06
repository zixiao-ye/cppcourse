#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <optional>

#include "hw08.h"

// convert string to unsigned short
std::optional<uint16_t> strtous(const char* str) {
    char* end;
    long val = strtol(str, &end, 10);
    if (errno || end == str || *end != '\0' || val < 0 || val >= 0x10000) {
        return {};
    }
    return static_cast<uint16_t>(val);
}

// Server listens in the given port, it accepts connections until killed via Ctrl + C on the
// terminal. It receives messages from the connection, concatinates them and sends the received
// chunk back to the client.
//
// TODO: Why not build in an option to shutdown the server when it receives a command 'kill'?
void server(uint16_t port) {
    net::Server srv { port };
    std::cout << "Server entering endless loop mode, press CTRL + C to exist (on most systems)\n";
    std::cout << "Or just restart the machine (jk jk)\n";

    while (true) {
        auto connection = srv.accept();

        std::stringstream complete;
        std::stringstream str;
        for (auto len = connection.receive(str); len != 0; len = connection.receive(str)) {
            if (len < 0) {
                throw std::runtime_error("Error reading from client");
            }

            // concatenate possible large messages to one complete
            complete << str.str();

            // Already send back the current part
            connection.send(str);
            str.clear();
        }
        std::cout << "Server received message from client: " << str.str() << "\n";
    }
}

// Client opens a connection on localhost to the given port, and sends the messages given via STDIN,
// to the server. It the waits for the server to response with the exact same message and prints
// that out again.
void client(uint16_t port) {
    net::Client clnt {};
    auto connection = clnt.connect(port);

    // Send a message from the command line
    std::string line;
    std::cout << "Type message to send to server: ";
    std::getline(std::cin, line);
    connection.send(line);

    // Receive the message again from the server
    ssize_t len = static_cast<ssize_t>(line.size());
    std::stringstream complete;

    // This just ensure that we don't wait for the socket to be closed
    while (len > 0) {
        std::ostringstream str;
        len -= connection.receive(str);
        complete << str.str();
    }
    std::cout << "Client received from server:    " << complete.str() << std::endl;
}

int main(int argc, char** argv) {
    // TODO: You can extend this main to connect to other IPs other than localhost
    auto usage = [&] {
        std::cout << "usage: " << argv[0] << " <server|client> <port>" << std::endl;
        exit(1);
    };

    // yeah argument parsing in C -.-
    if (argc != 3 or strcmp(argv[1], "--help") == 0) {
        usage();
    }

    /// Read the port
    auto maybe_port = strtous(argv[2]);
    if (not maybe_port.has_value()) {
        std::cout << "invalid port given: << " << argv[2] << std::endl;
        usage();
    }

    uint16_t port = maybe_port.value();

    // Dispatch to server or client
    if (strcmp(argv[1], "server") == 0) {
        server(port);
    } else if (strcmp(argv[1], "client") == 0) {
        client(port);
    } else {
        std::cout << "unknown operation mode " << argv[1] << std::endl;
        usage();
    }

    return 0;
}
