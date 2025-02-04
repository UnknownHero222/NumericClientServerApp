#include "config_parser.h"
#include <iostream>

using namespace common;

void BaseConfig::parse(int argc, char* argv[]) {
    po::options_description general_options("General options");
    general_options.add_options()
        ("help,h", "Help screen")
        ("config,c", po::value<std::string>(), "Path to config file");

    po::parsed_options parsed = po::command_line_parser(argc, argv)
        .options(general_options)
        .allow_unregistered()
        .run();
    
    po::store(parsed, vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << general_options << std::endl;
        exit(0);
    }
    std::ifstream config_file(vm["config"].as<std::string>());
    if (!config_file) {
        throw std::runtime_error("Failed to open config file");
    }

    parse_config_file(config_file);
}

void ServerConfig::parse_config_file(std::ifstream& config_file) {
   po::options_description config_options("Config options");
    config_options.add_options()
        ("host", po::value<std::string>(), "Server host")
        ("port", po::value<uint16_t>(), "Server port")
        ("dump_timeout_sec", po::value<int>(), "Dumping file with saved numbers timeout in seconds")
        ("dump_file_path", po::value<std::string>(), "Path to file with saved numbers")
        ("logs_directory_path", po::value<std::string>(), "Logs directory");

    po::store(po::parse_config_file(config_file, config_options, true), vm);
    po::notify(vm);
}

void ClientConfig::parse_config_file(std::ifstream& config_file) {
    po::options_description config_options("Client config");
    config_options.add_options()
        ("server_url", po::value<std::string>(), "Server URL")
        ("server_port", po::value<uint32_t>(), "Server port")
        ("workers_count", po::value<uint32_t>(), "Worker threads count")
        ("logs_directory_path", po::value<std::string>(), "Logs directory");

    po::store(po::parse_config_file(config_file, config_options, true), vm);
    po::notify(vm);
}
