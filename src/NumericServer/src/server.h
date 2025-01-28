#pragma once

#include "tcp_conn.hpp"
#include <atomic>
#include <boost/asio.hpp>
#include <cstdint>
#include <string>
#include <unordered_set>

namespace NumericServer {

using namespace boost::asio;

class Server {
public:
  Server() = default;
  Server(const std::string &host, uint32_t port);
  ~Server();
  void start();
  void stop();

private:
  uint32_t handle_numbers();

private:
  std::string host_;
  uint32_t port_;

  io_context io_context_;

  std::unordered_set<uint32_t> numbers_;
};

} // namespace NumericServer