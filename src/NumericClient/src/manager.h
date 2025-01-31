#pragma once

#include "client.h"

#include <thread>
#include <vector>

namespace NumericClient {

class ClientManager {
public:
  ClientManager(const std::string &host, uint16_t port, size_t client_count);
  ~ClientManager();

  void start();
  void stop();

private:
  void run_client();

private:
  std::string host_;
  uint16_t port_;
  size_t client_count_;

  std::vector<std::thread> client_threads_;
  bool is_running_{false};
};
} // namespace NumericClient
