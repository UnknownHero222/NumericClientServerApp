#include "server.h"
#include "SimpleLogger/simple_logger.h"
#include <fstream>
#include <iostream>
#include <random>

using namespace NumericServer;
using namespace common;

using namespace boost::asio::ip;

Server::Server(const ServerConfig &config, io_context &io_context)
    : config_(config), io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), config.port)) {
  SimpleLogger::set_service_name("NumericServer");

  start_accept();

  boost::asio::post(io_context_, [this]() { this->dump_numbers(); });

  is_running_ = true;
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

} catch (const std::exception &ex) {
  SimpleLogger::error_log("Exception: " + std::string(ex.what()));
}

void Server::stop() try {
  if (dump_timer_) {
    dump_timer_->cancel();
  }

  acceptor_.close();
  io_context_.stop();

  is_running_ = false;
} catch (const std::exception &ex) {
  SimpleLogger::error_log("Exception: " + std::string(ex.what()));
}

void Server::handle_request(uint32_t number,
                            std::function<void(uint32_t)> respond) {
  std::lock_guard<std::mutex> lock(mtx_);

  SimpleLogger::log("Number from the request " + std::to_string(number));

  numbers_.insert(number);
  respond(handle_numbers());
}

uint32_t Server::handle_numbers() {
  if (numbers_.empty()) {
    return 0;
  }

  uint32_t squares_sum{0};
  std::accumulate(numbers_.begin(), numbers_.end(), 0,
                  [&squares_sum](uint32_t sum, uint32_t number) {
                    squares_sum += number * number;
                    return sum;
                  });

  return squares_sum / numbers_.size();
}

void Server::dump_numbers() {
  if (numbers_.size() == 0) {
    return;
  }

  dump_timer_ = std::make_unique<boost::asio::steady_timer>(
      io_context_, std::chrono::seconds(config_.dump_interval_seconds));

  dump_timer_->async_wait([this](const boost::system::error_code &error) {
    if (!error && is_running_) {
      save_numbers_to_file();
      dump_numbers();
    }
  });

  SimpleLogger::log(std::to_string(numbers_.size()) +
                    " numbers saved to the file");
}

void Server::save_numbers_to_file() {
  std::ofstream file("numbers_dump", std::ios::binary);
  if (!file.is_open()) {
    SimpleLogger::error_log("Failed to open file for writing");
    return;
  }

  for (auto number : numbers_) {
    file.write(reinterpret_cast<const char *>(&number), sizeof(number));
  }

  file.close();
}