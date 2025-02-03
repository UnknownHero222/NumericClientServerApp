#include "manager.h"
#include "SimpleLogger/simple_logger.h"
#include "ConfigParser/config_parser.h"
#include <iostream>

using namespace common;
using namespace NumericClient;

int main(int argc, const char **argv) {
  ClientConfig config;
  config.parse(argc, const_cast<char **>(argv));

  ClientSettings settings{config.get<std::string>("server_url"),
                        config.get<uint16_t>("server_port"),
                        config.get<uint16_t>("workers_count"),
                        config.get<std::string>("logs_directory_path")};

  ClientManager client_manager(settings);
  client_manager.start();

  SimpleLogger::log("Press ENTER to stop clients...");
  std::cin.get();

  client_manager.stop();

  return 0;
}