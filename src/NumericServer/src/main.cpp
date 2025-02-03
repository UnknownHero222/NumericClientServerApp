#include "server.h"
#include "ConfigParser/config_parser.h"
#include <iostream>

using namespace common;
using namespace NumericServer;

static constexpr auto kHost = "127.0.0.1";
static constexpr auto kPort = 35123;

int main(int argc, const char **argv) {
  try {
    ServerConfig config;
    config.parse(argc, const_cast<char **>(argv));

    ServerSettings settings{config.get<std::string>("host"),
                            config.get<uint16_t>("port"),
                            config.get<int>("dump_timeout_sec")};

    boost::asio::io_context io_context;
    NumericServer::Server server(settings, io_context);

    std::cout << "Server is running on " << kHost << ":" << kPort << std::endl;

    io_context.run();
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}