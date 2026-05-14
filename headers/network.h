#ifndef NETWRK_H
#define NETWRK_H

#include "headers/client.h"
#include "headers/server.h"
class Network{
    public:
    Client client;
    Server server;

    Network() = default;
    void init();

    std::atomic<bool> is_ready{false};
};
#endif
