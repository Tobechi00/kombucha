#ifndef SERVER_H
#define SERVER_H

#include <atomic>
class Server{
    public:
    Server() = default;
    void init();

    std::atomic <bool> listening{false};
};
#endif
