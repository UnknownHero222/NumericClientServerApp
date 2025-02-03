#pragma once

#include "client.h"
#include "client_structs.h"

#include <thread>
#include <vector>

namespace NumericClient {

class ClientManager {
public:
  ClientManager(const ClientSettings &settings);
  ~ClientManager();

  void start();
  void stop();

private:
  void run_client();

private:
  ClientSettings settings_;

  std::vector<std::thread> client_threads_;
  bool is_running_{false};
};
} // namespace NumericClient
