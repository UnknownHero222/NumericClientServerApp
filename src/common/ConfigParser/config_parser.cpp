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
    postprocess_options();
}

void ServerConfig::parse_config_file(std::ifstream& config_file) {
    po::options_description config_options("Server config");
    config_options.add_options()
        ("server.host", po::value<std::string>()->default_value("0.0.0.0"), "Server host")
        ("server.port", po::value<uint16_t>()->required(), "Server port")
        ("server.dump_timeout_sec", po::value<int>()->default_value(60), "Dump timeout");

    auto parsed = po::parse_config_file(config_file, config_options, true);
    po::store(parsed, vm);
    po::notify(vm);
}

void ServerConfig::postprocess_options() {
    if (vm.count("server.host")) {
        vm.emplace("host", vm["server.host"]);
    }
    if (vm.count("server.port")) {
        vm.emplace("port", vm["server.port"]);
    }
    if (vm.count("server.dump_timeout_sec")) {
        vm.emplace("dump_timeout_sec", vm["server.dump_timeout_sec"]);
    }

    if (!vm.count("host") || !vm.count("port")) {
        throw po::error("Missing required server parameters");
    }
}

void ClientConfig::parse_config_file(std::ifstream& config_file) {
    po::options_description config_options("Client config");
    config_options.add_options()
        ("client.server_url", po::value<std::string>(), "Server URL")
        ("client.server_port", po::value<uint16_t>(), "Server port")
        ("client.workers_count", po::value<int>(), "Worker threads count");

    auto parsed = po::parse_config_file(config_file, config_options, true);
    po::store(parsed, vm);
    po::notify(vm);
}

void ClientConfig::postprocess_options() {
    if (vm.count("client.server_url")) {
        vm.emplace("server_url", vm["client.server_url"]);
    }
    if (vm.count("client.server_port")) {
        vm.emplace("server_port", vm["client.server_port"]);
    }
    if (vm.count("client.workers_count")) {
        vm.emplace("workers_count", vm["client.workers_count"]);
    }
}
