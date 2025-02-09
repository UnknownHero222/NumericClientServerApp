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
                 process_request) {
    process_request_ = process_request;
    do_read();
  }

private:
  TcpConnection(boost::asio::io_context &io_context) : socket_(io_context) {}

  void do_read() {
    auto self = shared_from_this();
    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(message_), '\n',
        [this, self](const boost::system::error_code &error,
                     size_t bytes_transferred) {
          if (!error) {
            try {
              uint32_t number = std::stoul(message_);
              message_.clear();

              process_request_(
                  number, [this, self](uint32_t result) { do_write(result); });
            } catch (const std::exception &e) {
              std::cerr << "Error parsing number: " << e.what() << std::endl;
            }
          } else {
            std::cerr << "Read error: " << error.message() << std::endl;
          }
        });
  }

  void do_write(uint32_t number) {
    auto self = shared_from_this();
    std::string response = std::to_string(number) + "\n";

    boost::asio::async_write(
        socket_, boost::asio::buffer(response),
        [this, self](const boost::system::error_code &error,
                     size_t /*bytes_transferred*/) {
          if (error) {
            std::cerr << "Write error: " << error.message() << std::endl;
          }
        });
  }

  void handle_write(const boost::system::error_code & /*error*/,
                    size_t /*bytes_transferred*/) {}

private:
  tcp::socket socket_;
  std::string message_;

  std::function<void(uint32_t, std::function<void(uint32_t)>)> process_request_;
};

} // namespace NumericServer