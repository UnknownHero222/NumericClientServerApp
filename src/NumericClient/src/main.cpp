#include "manager.h"
#include "SimpleLogger/simple_logger.h"
#include "ConfigParser/config_parser.h"
#include <iostream>

using namespace common;
using namespace NumericClient;

static constexpr auto kHost = "127.0.0.1";
static constexpr auto kPort = 35123;
static constexpr auto kClientCount = 5;

int main(int argc, const char **argv) {
  ClientConfig config;
  config.parse(argc, const_cast<char **>(argv));

  ClientSettings settings{config.get<std::string>("server.host"),
                        config.get<uint16_t>("server.port"),
                        config.get<uint16_t>("client.workers_count"),
                        config.get<std::string>("client.log_file_path")};

  ClientManager client_manager(settings);
  client_manager.start();

  SimpleLogger::log("Press ENTER to stop clients...");
  std::cin.get();

  client_manager.stop();

  return 0;
}