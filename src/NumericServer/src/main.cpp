#include "server.h"
#include <iostream>

using namespace NumericServer;

static constexpr auto kHost = "127.0.0.1";
static constexpr auto kPort = 35123;

int main() {
  try {
    boost::asio::io_context io_context;
    NumericServer::Server server(kHost, kPort, io_context);

    std::cout << "Server is running on " << kHost << ":" << kPort << std::endl;

    io_context.run();
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}