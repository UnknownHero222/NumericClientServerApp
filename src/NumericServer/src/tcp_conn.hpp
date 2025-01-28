#pragma once

#include <boost/asio.hpp>
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
                 process_request) {
    process_request_ = process_request;
    // TODO: Implement reading from the socket
  }

private:
  TcpConnection(boost::asio::io_context &io_context) : socket_(io_context) {}

  void handle_write(const boost::system::error_code & /*error*/,
                    size_t /*bytes_transferred*/) {}

private:
  tcp::socket socket_;
  std::string message_;

  std::function<void(uint32_t, std::function<void(uint32_t)>)> process_request_;
};

} // namespace NumericServer