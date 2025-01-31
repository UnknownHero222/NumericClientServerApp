#include "manager.h"
#include "simple_logger.h"
#include <iostream>

using namespace common;
using namespace NumericClient;

static constexpr auto kHost = "127.0.0.1";
static constexpr auto kPort = 35123;
static constexpr auto kClientCount = 5;

int main() {
  ClientManager client_manager(kHost, kPort, kClientCount);
  client_manager.start();

  SimpleLogger::log("Press ENTER to stop clients...");
  std::cin.get();

  client_manager.stop();

  return 0;
}