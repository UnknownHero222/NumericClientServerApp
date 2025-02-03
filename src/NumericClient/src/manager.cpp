#include "manager.h"
#include "SimpleLogger/simple_logger.h"
#include <chrono>
#include <iostream>

using namespace common;
using namespace NumericClient;

ClientManager::ClientManager(const ClientSettings &settings)
    : settings_(settings) {
  is_running_ = true;

  SimpleLogger::set_service_name("NumericClient");
}

ClientManager::~ClientManager() { stop(); }

void ClientManager::start() {

  SimpleLogger::log("Starting " + std::to_string(settings_.workers_count) +
                    " clients...");

  for (size_t i = 0; i < settings_.workers_count; ++i) {
    client_threads_.emplace_back(&ClientManager::run_client, this);
  }
}

void ClientManager::stop() {
  if (!is_running_)
    return;

  is_running_ = false;

  SimpleLogger::log("Stopping clients...");

  for (auto &thread : client_threads_) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  client_threads_.clear();
}

void ClientManager::run_client() {
  NumericClient::Client client(settings_.server_url, settings_.server_port);

  while (is_running_) {
    client.send_request();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
