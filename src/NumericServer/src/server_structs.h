#pragma once

#include <cstdint>
#include <string>

namespace NumericServer {

struct ServerConfig {
  std::string host;
  uint32_t port;
  uint32_t dump_interval_seconds;
};

} // namespace NumericServer