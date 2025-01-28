#include "server.h"
#include <iostream>
#include <random>

using namespace NumericServer;

using namespace boost::asio::ip;

Server::Server(const std::string &host, uint32_t port)
    : host_(host), port_(port), is_running_(false) {}

void Server::start() try {
  is_running_ = true;

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
  is_running_ = false;

  
  io_context_.stop();

} catch (const boost::exception &ex) {
  std::cerr << "Boost exception" << std::endl;
} catch (const std::exception &ex) {
  std::cerr << "Exception: " << ex.what() << std::endl;
}