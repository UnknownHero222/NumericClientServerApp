#include "simple_logger.h"

using namespace common;

std::string SimpleLogger::service_name_;
std::string SimpleLogger::log_filepath_;

void SimpleLogger::config_setup(const std::string &name,
                                const std::string &log_filepath) {
  service_name_ = name;

  std::string clean_log_path = log_filepath;
  if (!clean_log_path.empty() && clean_log_path.front() == '"' &&
      clean_log_path.back() == '"') {
    clean_log_path = clean_log_path.substr(1, clean_log_path.size() - 2);
  }

  if (clean_log_path.empty() || clean_log_path.back() != '/') {
    clean_log_path += "/";
  }

  log_filepath_ = clean_log_path + service_name_ + ".log";

  std::cout << "Log file path: " << log_filepath_ << std::endl;

  std::filesystem::create_directories(clean_log_path);
}

void SimpleLogger::log(const std::string &message) { write_log("", message); }

void SimpleLogger::error_log(const std::string &message) {
  write_log("[err]", message);
}

void SimpleLogger::write_log(const std::string &prefix,
                             const std::string &message) {
  std::string log_entry =
      service_name_ + "-" + get_current_time() + ":" + prefix + " " + message;

  std::cout << log_entry << std::endl;

  if (!std::filesystem::exists(log_filepath_)) {
    std::ofstream log_file(log_filepath_, std::ios::out);
    if (!log_file) {
      std::cerr << "Error: Unable to create log file: ";
      return;
    }
    log_file.close();
  }

  std::ofstream log_file(log_filepath_, std::ios::app);
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
