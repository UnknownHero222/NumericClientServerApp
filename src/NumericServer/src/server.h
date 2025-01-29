#pragma once

#include "tcp_conn.hpp"
#include <atomic>
#include <boost/asio.hpp>
#include <cstdint>
#include <string>
#include <thread>
#include <unordered_set>

namespace NumericServer {

using namespace boost::asio;

class Server {
public:
  explicit Server(const std::string &host, uint32_t port,
                  io_context &io_context);
  ~Server();
  void start_accept();
  void stop();

private:
  void handle_request(uint32_t number, std::function<void(uint32_t)> respond);
  uint32_t handle_numbers();
  void dump_numbers();

private:
  std::string host_;
  uint32_t port_;

  io_context &io_context_;
  ip::tcp::acceptor acceptor_;

  std::unordered_set<uint32_t> numbers_;

  std::thread dumping_thread_;
  bool is_running_{false};
};

} // namespace NumericServer