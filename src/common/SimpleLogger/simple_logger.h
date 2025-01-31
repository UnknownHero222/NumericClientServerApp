#pragma once

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

namespace common {

class SimpleLogger {
public:
  static void set_service_name(const std::string &name);
  static void log(const std::string &message);
  static void error_log(const std::string &message);

private:
  static std::string get_current_time();
  static void write_log(const std::string &prefix, const std::string &message);

private:
  static std::string service_name_{"DefaultService"};
  static std::string log_filepath_;
};
} // namespace common
