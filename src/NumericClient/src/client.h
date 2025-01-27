#pragma once

#include <string>
#include <cstdint>

namespace NumericClient {

class Client { 
public:
    Client(const std::string& host, uint16_t port);
    void start();
    void stop();

private:
    uint16_t generate_random_number();

private:
    std::string host_;
    uint16_t port_;
    bool is_running_;
};

}