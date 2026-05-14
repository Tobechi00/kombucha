#ifndef UTIL_H
#define UTIL_H

#include "headers/subnet.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <vector>

namespace util{
    //returns current network ip_address and subnet_mask
    extern Subnet get_network_address();

    //used returns true if addr is a loopback addr
    extern bool check_loopback(in_addr &in_addr);

    //returns a list of all possible ip addresses on network
    extern std::vector<in_addr_t> get_ip_addrs(Subnet subnet);
}

#endif
