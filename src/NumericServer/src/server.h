#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <string>

namespace NumericServer {

using namespace boost::asio;

class Server {
public:
  Server() = default;
  ~Server() = default;
  Server(const std::string &host, uint32_t port);
  void start();
  void stop();

private:
  uint16_t generate_random_number();

private:
  std::string host_;
  uint32_t port_;
  bool is_running_;

  io_context io_context_;
};

} // namespace NumericClient