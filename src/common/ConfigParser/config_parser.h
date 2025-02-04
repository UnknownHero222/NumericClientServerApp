#pragma once

#include <boost/program_options.hpp>
#include <fstream>
#include <string>

namespace common {

namespace po = boost::program_options;

class BaseConfig {
protected:
    po::variables_map vm;

public:
    virtual ~BaseConfig() = default;

    void parse(int argc, char* argv[]);

    template<typename T>
    T get(const std::string& key) const {
        return vm[key].as<T>();
    }

protected:
    virtual void parse_config_file(std::ifstream& config_file) = 0;
};

class ServerConfig : public BaseConfig {
public:
    void parse_config_file(std::ifstream& config_file) override;
};

class ClientConfig : public BaseConfig {
public:
    void parse_config_file(std::ifstream& config_file) override;
};

} // namespace common
