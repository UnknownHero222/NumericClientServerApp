#pragma once

#include <cstdint>
#include <string>

namespace NumericServer {

struct ServerSettings {
  std::string host;
  uint32_t port;
  int dump_interval_seconds;
  std::string dump_file_path;
  std::string logs_directory_path;
};

} // namespace NumericServer