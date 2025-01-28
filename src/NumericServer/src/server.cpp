#include "server.h"
#include <iostream>
#include <random>

using namespace NumericServer;

using namespace boost::asio::ip;

Server::Server(const std::string &host, uint32_t port)
    : host_(host), port_(port) {}

Server::~Server() { stop(); }

void Server::start() try {

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}

void Server::stop() try {

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
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