#include "simple_logger.h"

using namespace common;

std::string SimpleLogger::service_name_ = "DefaultService";
std::string SimpleLogger::log_file_ = "logs/log.txt";

void SimpleLogger::set_service_name(const std::string &name) {
  service_name_ = name;
  log_file_ = "logs/" + service_name_ + ".log";

  std::filesystem::create_directories("logs");
}

void SimpleLogger::log(const std::string &message) {
  write_log("", message);
}

void SimpleLogger::error_log(const std::string &message) {
  write_log("[err]", message);
}

void SimpleLogger::write_log(const std::string &prefix, const std::string &message) {
  std::string log_entry = "[" + service_name_ + "] [" + get_current_time() + "] " + prefix + " " + message;

  std::cout << log_entry << std::endl;

  std::ofstream log_file(log_file_, std::ios::app);
  if (log_file.is_open()) {
    log_file << log_entry << std::endl;
  }
}

std::string SimpleLogger::get_current_time() {
  std::time_t now = std::time(nullptr);
  std::tm tm_buf;
  localtime_r(&now, &tm_buf);

  char buffer[20];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_buf);
  return std::string(buffer);
}
