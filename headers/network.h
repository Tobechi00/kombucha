#ifndef NETWRK_H
#define NETWRK_H

#include "headers/sender.h"
#include "headers/listener.h"

#include <string>
class Network{
    public:
    Sender sender;
    Listener listener;

    Network() = default;
    void init();
    int send(std::string file_name);

    std::atomic<bool> is_ready{false};
};
#endif
