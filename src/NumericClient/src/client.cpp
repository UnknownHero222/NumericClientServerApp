#include "client.h"
#include <iostream>
#include <random>

using namespace NumericClient;

static constexpr auto kMinRandomNumber = 0;
static constexpr auto kMaxRandomNumber = 1023;

Client::Client(const std::string& host, uint16_t port) : host_(host), port_(port), is_running_(false) {}

void Client::start() {
    is_running_ = true;
    //TODO
}

void Client::stop() {
    is_running_ = false;
    //TODO
}

uint16_t Client::generate_random_number() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> dis(kMinRandomNumber, kMaxRandomNumber);

    return dis(gen);
}