#ifndef Listener_H
#define Listener_H

#include <atomic>

class Listener{
    public:
    Listener() = default;
    void init();

    std::atomic <bool> listening{false};
    std::atomic <bool> connected{false};
};
#endif
