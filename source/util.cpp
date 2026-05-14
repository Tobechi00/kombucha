#include "headers/util.h"
#include "headers/subnet.h"
#include <netinet/in.h>
#include <sys/_endian.h>
#include <sys/_types/_in_addr_t.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <iostream>
#include <arpa/inet.h>
#include <vector>

typedef struct { int a; int b; } y;

namespace util{

    Subnet get_network_address(){
        //refrence: https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/getifaddrs.3.html
        ifaddrs *addrs;

        if(getifaddrs(&addrs) == -1){
            //temporary holder
            std::cout << "err \n";
            return {0, 0};
        }

        in_addr_t ip = 0;
        in_addr_t netmask = 0;

        while(addrs != nullptr){

            //check for ipv4 addresses only!!

            //refrence
            sockaddr *r_ip_addr = addrs -> ifa_addr;

            if(r_ip_addr -> sa_family != AF_INET){//address family internet ipv4
                addrs = addrs ->ifa_next;
                continue;
            }

            sockaddr_in *ip_addr = (sockaddr_in*) r_ip_addr;

            if(check_loopback(ip_addr->sin_addr)){
                addrs = addrs->ifa_next;
                continue;
            }

            sockaddr *r_netmask_addr = addrs -> ifa_netmask;
            sockaddr_in *netmask_addr = (sockaddr_in*) r_netmask_addr;

            //The inet_ntoa function converts an (Ipv4) Internet network address into an ASCII string in Internet standard dotted-decimal format.
            // std::cout << "ip_address: "<< inet_ntoa(ip_addr -> sin_addr) << "\n";
            // std::cout << "subnet_mask:" << inet_ntoa(netmask_addr -> sin_addr) << "\n";
            // std::cout <<"\n";

            ip = htonl(ip_addr -> sin_addr.s_addr);
            netmask = htonl(netmask_addr -> sin_addr.s_addr);
            break;

            // addrs = addrs ->ifa_next;
        }

        return {ip, netmask};
        //sockaddr_storage is guaranteed to be large enough to store any other sockaddr_ type. If you need to store a sockaddr by value but don't know what type of sockaddr you want to store, use a sockaddr_storage.
    }

    bool check_loopback(in_addr &in_addr){

        const in_addr_t loop_back = 0x7f000000;//127.0.0.0

        //htonl converts host order to network order
        in_addr_t reslt = htonl(in_addr.s_addr) & loop_back;//s_addr uses typedef for in_addr_t as uint32_t; seeing as ipv4 is 32 bits

        return reslt == loop_back;
    }

    std::vector<in_addr_t> get_ip_addrs(Subnet subnet){

        std::vector<in_addr_t> addrs_list;

        in_addr_t max_netmask = 0xffffffff; //255.255.255.255
        in_addr_t pos_addrs = (max_netmask - subnet.netmask);//addr range

        //strip prefix
        in_addr_t network_address = subnet.ip & subnet.netmask;//isolate network prefix
        in_addr_t max_ip_addr = network_address + pos_addrs;

        //calculate broad cast address
        in_addr_t broadcast_addr = network_address | (~subnet.netmask); //(netadress) or (inverted subnet mask);

        for(in_addr_t addrs = network_address; addrs <=  max_ip_addr; addrs++){
            if(addrs == broadcast_addr){
                continue;
            }

            addrs_list.push_back(addrs);
        }

        return addrs_list;
    }

}
