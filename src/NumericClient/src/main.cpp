#include "client.h"
#include <iostream>

using namespace NumericClient;

int main() {
  NumericClient::Client client("127.0.0.1", 35123);

  std::cout << "Client started. Sending requests..." << std::endl;

  while (true) {
    client.send_request();

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}