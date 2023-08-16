/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// if you activate this, doctest won't swallow exceptions
// #define DOCTEST_CONFIG_NO_EXCEPTIONS

#include <doctest/doctest.h>

#ifndef DOCTEST_REQUIRE_NOTHROW
#define DOCTEST_REQUIRE_NOTHROW(x)                                               do {                                                                             x;                                                                           } while (0)
#endif

#include "hw08.h"

#include <chrono>
#include <future>
#include <random>
#include <sys/socket.h>
#include <thread>

// require at least c++20
static_assert(__cplusplus >= 202002L);

TEST_CASE("Testing FileDescriptor") {
  static_assert(!std::is_copy_assignable_v<net::FileDescriptor>,
                "FileDescriptor should not be copy assignable");
  static_assert(!std::is_copy_constructible_v<net::FileDescriptor>,
                "FileDescriptor should not be copy constructible");

  SUBCASE("Default construct FileDescriptor") {
    net::FileDescriptor fd;

    CHECK_EQ(fd.unwrap(), -1);
  }

  SUBCASE("Construct FileDescriptor and move") {
    net::FileDescriptor fd{4};

    CHECK_EQ(fd.unwrap(), 4);

    auto moved{std::move(fd)};
    CHECK_EQ(fd.unwrap(), -1);
    CHECK_EQ(moved.unwrap(), 4);
  }
}

TEST_CASE("Open a socket") {
  SUBCASE("Should no throw") { CHECK_NOTHROW(net::Socket socket); }

  SUBCASE("Socket should be valid") {
    net::Socket socket;

    CHECK_UNARY(socket.fd() > 0);
  }

  SUBCASE("Accept first before listening on socket") {
    net::Socket socket;

    CHECK_THROWS(socket.accept());
  }

  SUBCASE("Try to listen") {
    net::Socket socket;

    CHECK_NOTHROW(socket.listen(1337));
    CHECK_UNARY(net::is_listening(socket.fd()));
  }

  SUBCASE("Are you closing your file descriptor?") {
    int fd;
    {
      net::Socket socket;
      fd = socket.fd();
    }

    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);

    INFO("error getting socket error code: ", std::string(strerror(retval)));
    CHECK_NE(retval, 0);
    CHECK_EQ(error, 0);
  }

  SUBCASE("Check socket is invalid after connection is closed") {
    // Just start the server, don't accept any messages
    net::Server srv{1337};

    net::Socket socket;
    int fd = socket.fd();

    {
      auto connection = socket.connect(1337);
      CHECK_NE(socket.fd(), fd);
      CHECK_EQ(connection.fd(), fd);
    }

    CHECK_NE(socket.fd(), fd);
  }
}

std::string random_string(std::string::size_type length) {
  auto randchar = []() -> char {
    constexpr std::string_view chars =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::mt19937 rg{std::random_device{}()};
    std::uniform_int_distribution<std::string::size_type> pick(0, chars.size() -
                                                                      1);
    return chars[pick(rg)];
  };

  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

TEST_CASE("Connect multiple times from client") {
  const std::string_view data = "Soo much data to send";

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection1 = client.connect(1337);

    std::ostringstream str;
    connection1.receive_all(str);
    str << ".....";

    auto connection2 = client.connect(1337);
    connection2.receive_all(str);
  };

  auto future = std::async(tmp);

  server_thread.join();
  CHECK_THROWS(future.get());
}

TEST_CASE("Testing client server with short messages 1") {
  const std::string_view data = "Soo much data to send";

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect(1337);

    std::ostringstream str;
    connection.receive(str);
    return str.str();
  };

  auto future = std::async(tmp);

  server_thread.join();
  auto received = future.get();

  CHECK_EQ(received, data);
}

TEST_CASE("Test messages of size 128 can be send in one chunk") {
  const std::string data = random_string(128);

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect(1337);

    std::ostringstream str;
    connection.receive(str);
    return str.str();
  };

  auto future = std::async(tmp);

  server_thread.join();
  auto received = future.get();

  CHECK_EQ(received, data);
}

TEST_CASE("Test messages of size 129 can be send in one chunk") {
  const std::string data = random_string(129);

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect(1337);

    std::ostringstream str;
    connection.receive(str);
    return str.str();
  };

  auto future = std::async(tmp);

  server_thread.join();
  auto received = future.get();

  CHECK_EQ(received.size(), 128);
  CHECK_UNARY(std::equal(received.begin(), received.end(), data.begin()));
}

TEST_CASE("Testing client server 1") {
  const std::string_view data = "Soo much data to send";

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect(1337);

    std::ostringstream str;
    connection.receive_all(str);
    return str.str();
  };

  auto future = std::async(tmp);

  server_thread.join();
  auto received = future.get();

  CHECK_EQ(received, data);
}

TEST_CASE("Testing client server 2") {
  const std::string_view data = "rofl";

  net::Server srv{1337};
  std::thread server_thread([&]() {
    auto connection = srv.accept();
    connection.send(data);
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect("127.0.0.1", 1337);

    std::ostringstream str;
    connection.receive_all(str);
    return str.str();
  };

  auto future = std::async(tmp);

  server_thread.join();
  auto received = future.get();

  CHECK_EQ(received, data);
}

TEST_CASE("Testing client server 3") {
  // Just create 100 random string of different lengths
  for (int i = 0; i < 10; ++i) {
    const std::string data = random_string(i * 4 + 50);

    CAPTURE(data);

    net::Server srv{1337};
    std::thread server_thread([&]() {
      auto connection = srv.accept();
      connection.send(data);
    });

    const auto tmp = [&]() {
      net::Client client{};
      auto connection = client.connect("127.0.0.1", 1337);

      std::ostringstream str;
      connection.receive_all(str);
      return str.str();
    };

    auto future = std::async(tmp);

    server_thread.join();
    auto received = future.get();

    CHECK_EQ(received, data);
  }
}

TEST_CASE("Receiving large messages") {
  std::mt19937 rg{std::random_device{}()};

  // randomly choose a multiplier
  std::uniform_int_distribution<std::size_t> pick(32, 128);

  // And choose a semi random offset, this makes everything less deterministic,
  // but makes it harder to just hard code certain values in the code :D
  const auto p1 = std::chrono::system_clock::now();
  auto offset =
      std::chrono::duration_cast<std::chrono::hours>(p1.time_since_epoch())
          .count() %
      1024;

  for (int i = 0; i < 4; ++i) {
    const std::string data = random_string(256 * pick(rg) + offset);

    CAPTURE(data);

    net::Server srv{1337};
    std::thread server_thread([&]() {
      auto connection = srv.accept();
      connection.send(data);
    });

    const auto tmp = [&]() {
      net::Client client{};
      auto connection = client.connect("127.0.0.1", 1337);

      std::ostringstream str;
      connection.receive_all(str);
      return str.str();
    };

    auto future = std::async(tmp);

    server_thread.join();
    auto received = future.get();

    CHECK_EQ(received, data);
  }
}

TEST_CASE("Testing multi client server") {
  const std::string data = random_string(200);

  net::Server srv{1337};
  std::thread server_thread([&]() {
    for (int i = 0; i < 5; ++i) {
      auto connection = srv.accept();
      connection.send(data);
    }
  });

  const auto tmp = [&]() {
    net::Client client{};
    auto connection = client.connect("127.0.0.1", 1337);

    std::ostringstream str;
    connection.receive_all(str);
    return str.str();
  };

  auto future1 = std::async(tmp);
  auto future2 = std::async(tmp);
  auto future3 = std::async(tmp);
  auto future4 = std::async(tmp);
  auto future5 = std::async(tmp);

  CHECK_EQ(future1.get(), data);
  CHECK_EQ(future2.get(), data);
  CHECK_EQ(future3.get(), data);
  CHECK_EQ(future4.get(), data);
  CHECK_EQ(future5.get(), data);
  server_thread.join();
}
