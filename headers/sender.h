#ifndef Sender_H
#define Sender_H

#include <atomic>
#include <sys/_types/_in_addr_t.h>
class Sender{
    public:
    Sender() = default;
    void init();
    int try_conn(in_addr_t address);
    //send


    std::atomic<bool> is_ready{false};
};
#endif
