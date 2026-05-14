#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
class Client{
    public:
    Client() = default;
    void init();

    std::atomic<bool> is_ready{false};
};
#endif
