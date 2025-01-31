#include "tcp_conn.h"
#include "simple_logger.h"

using namespace NumericServer;
using namespace common;

void TcpConnection::start(
    std::function<void(uint32_t, std::function<void(uint32_t)>)>
        process_request) {
  process_request_ = process_request;
  do_read();
}

void TcpConnection::do_read() try {
  auto self = shared_from_this();

  boost::asio::async_read_until(
      socket_, boost::asio::dynamic_buffer(message_), '\n',
      [this, self](const boost::system::error_code &error,
                   size_t bytes_transferred) {
        if (!error) {
          uint32_t number = std::stoul(message_);
          message_.clear();

          process_request_(number,
                           [this, self](uint32_t result) { do_write(result); });
        } else {
          SimpleLogger::error_log("Read error: " + error.message());
        }
      });
} catch (const std::exception &ex) {
  SimpleLogger::error_log("Exception: " + std::string(ex.what()));
}

void TcpConnection::do_write(uint32_t number) {
  auto self = shared_from_this();
  std::string response = std::to_string(number) + "\n";

  boost::asio::async_write(socket_, boost::asio::buffer(response),
                           [this, self](const boost::system::error_code &error,
                                        size_t bytes_transferred) {
                             if (error) {
                               std::cerr << "Write error: " << error.message()
                                         << std::endl;
                             }
                           });
}