#include "server.h"
#include "ConfigParser/config_parser.h"
#include <iostream>

using namespace common;
using namespace NumericServer;

int main(int argc, const char **argv) {
  try {
    ServerConfig config;
    config.parse(argc, const_cast<char **>(argv));

    ServerSettings settings{config.get<std::string>("host"),
                            config.get<uint16_t>("port"),
                            config.get<int>("dump_timeout_sec"), 
                            config.get<std::string>("dump_file_path"),
                            config.get<std::string>("logs_directory_path")};

    boost::asio::io_context io_context;
    NumericServer::Server server(settings, io_context);

    io_context.run();
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}