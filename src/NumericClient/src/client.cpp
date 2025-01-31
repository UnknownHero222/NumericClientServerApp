#include "client.h"
#include "simple_logger.h"
#include <iostream>
#include <random>

using namespace NumericClient;

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace common;

static constexpr auto kMinRandomNumber = 0;
static constexpr auto kMaxRandomNumber = 1023;

Client::Client(const std::string &host, uint16_t port)
    : io_context_(), socket_(io_context_), endpoint_(make_address(host), port) {
}

void Client::send_request() try {
  socket_.connect(endpoint_);

  std::string message = std::to_string(generate_random_number());
  boost::asio::write(socket_, buffer(message + "\n"));
  SimpleLogger::log("Request to server: " + message);

  std::string response;
  boost::asio::streambuf response_buffer;
  boost::asio::read_until(socket_, response_buffer, '\n');

  std::istream response_stream(&response_buffer);
  std::getline(response_stream, response);

  SimpleLogger::log("Response from server: " + response);

  socket_.close();
} catch (const std::exception &ex) {
  SimpleLogger::error_log("Exception: " + std::string(ex.what()));
}

uint16_t Client::generate_random_number() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint16_t> dis(kMinRandomNumber,
                                              kMaxRandomNumber);

  return dis(gen);
}