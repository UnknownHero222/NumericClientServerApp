#include "client.h"
#include <iostream>

using namespace NumericClient;

static constexpr auto kHost = "127.0.0.1";
static constexpr auto kPort = 35123;

int main() {
  NumericClient::Client client(kHost, kPort);

  std::cout << "Client started. Sending requests..." << std::endl;

  while (true) {
    client.send_request();

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}