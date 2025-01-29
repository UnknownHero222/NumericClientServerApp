#include "server.h"
#include <iostream>
#include <random>
#include <fstream>

using namespace NumericServer;

using namespace boost::asio::ip;

Server::Server(const std::string &host, uint32_t port, io_context &io_context)
    : host_(host), port_(port), io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
  start_accept();
  is_running_ = true;

  dumping_thread_ = std::thread(&Server::dump_numbers, this);
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

  if (dumping_thread_.joinable()) {
    dumping_thread_.join();
  }

  is_running_ = false;

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}

void Server::handle_request(uint32_t number,
                            std::function<void(uint32_t)> respond) {
  std::cout << "Get the number from the request: " << number << std::endl;
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

void Server::dump_numbers() {
  while (is_running_) {
    std::cout << "Dumping numbers..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    if (numbers_.empty()) {
      continue;
    }
 
    std::ofstream file("numbers_dump", std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Failed to open file for writing.\n";
      return;
    }

    for (auto number : numbers_) {
      file.write(reinterpret_cast<const char*>(&number), sizeof(number));
    }

    file.close();
  }
}