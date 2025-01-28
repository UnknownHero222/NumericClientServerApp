#include "server.h"
#include <iostream>
#include <random>

using namespace NumericServer;

using namespace boost::asio::ip;

Server::Server(const std::string &host, uint32_t port, io_context &io_context)
    : host_(host), port_(port), io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
  start_accept();
}

Server::~Server() { stop(); }

void Server::start_accept() try {
  TcpConnection::Pointer new_connection = TcpConnection::create(io_context_);

  acceptor_.async_accept(
      new_connection->socket(),
      [this, new_connection](const boost::system::error_code &error) {
        if (!error) {
          new_connection->start(
              [this](uint32_t number, std::function<void(uint32_t)> respond) {
                handle_request(number, respond);
              });
        }
        start_accept();
      });

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}

void Server::stop() try {
  acceptor_.close();
  io_context_.stop();
} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}

void Server::handle_request(uint32_t number,
                            std::function<void(uint32_t)> respond) {
  numbers_.insert(number);
  respond(handle_numbers());
}

uint32_t Server::handle_numbers() {
  if (numbers_.empty()) {
    return 0;
  }

  uint32_t squares_sum = 0;
  for (auto number : numbers_) {
    squares_sum += number * number;
  }

  return squares_sum / numbers_.size();
}