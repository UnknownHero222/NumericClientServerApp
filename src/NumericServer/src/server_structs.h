#pragma once

#include <cstdint>
#include <string>

namespace NumericServer {

struct ServerSettings {
  std::string host;
  uint32_t port;
  uint32_t dump_interval_seconds;
  std::string dump_file_path;
  std::string log_file_path;
};

} // namespace NumericServer