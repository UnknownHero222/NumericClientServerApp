#include "server.h"
#include <iostream>
#include <random>

using namespace NumericServer;

using namespace boost::asio::ip;

Server::Server(const std::string &host, uint32_t port)
    : host_(host), port_(port), is_running_(false) {}

Server::~Server() { stop(); }

void Server::start() try {
  if (is_running_.exchange(true)) {
    std::cerr << "Server is already running." << std::endl;
    return;
  }

  tcp::acceptor acceptor(
      io_context_, tcp::endpoint(boost::asio::ip::make_address(host_), port_));

  std::cout << "Server is running on " << host_ << ":" << port_ << std::endl;

  while (true) {
    tcp::socket socket(io_context_);
    acceptor.accept(socket);

    std::string message = "Simple response";
    boost::asio::write(socket, boost::asio::buffer(message));
  }

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}

void Server::stop() try {
  if (!is_running_.exchange(true)) {
    std::cerr << "Server is dead" << std::endl;
    return;
  }

  io_context_.stop();

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}