#pragma once

#include <boost/asio.hpp>
#include <cstdint>
#include <string>

namespace NumericClient {

class Client {
public:
  Client(const std::string &host, uint16_t port);

  void send_request();

private:
  uint16_t generate_random_number();

private:
  boost::asio::io_context io_context_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::ip::tcp::endpoint endpoint_;
  bool is_running_{false};
};

} // namespace NumericClient