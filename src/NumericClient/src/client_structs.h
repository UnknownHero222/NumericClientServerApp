#pragma once

#include <cstdint>
#include <string>

namespace NumericClient {

struct ClientSettings {
  std::string server_url;
  uint32_t server_port;
  uint32_t workers_count;
  std::string logs_directory_path;
};

} // namespace NumericClient