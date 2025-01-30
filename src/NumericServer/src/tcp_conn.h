#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

namespace NumericServer {

using namespace boost::asio;
using namespace boost::asio::ip;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
  using Pointer = std::shared_ptr<TcpConnection>;

  static Pointer create(boost::asio::io_context &io_context) {
    return Pointer(new TcpConnection(io_context));
  }

  tcp::socket &socket() { return socket_; }

  void start(std::function<void(uint32_t, std::function<void(uint32_t)>)>
                 process_request);

private:
  TcpConnection(boost::asio::io_context &io_context) : socket_(io_context) {}

  void do_read();

  void do_write(uint32_t number);

private:
  tcp::socket socket_;
  std::string message_;

  std::function<void(uint32_t, std::function<void(uint32_t)>)> process_request_;
};

} // namespace NumericServer