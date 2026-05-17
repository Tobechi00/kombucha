#include "headers/network.h"
#include "headers/listener.h"
#include "headers/subnet.h"
#include "headers/util.h"
#include <sys/_types/_in_addr_t.h>
#include <thread>
#include <vector>
#include <iostream>

void Network::init(){
    //on startup initialize listener
    std::thread listener_worker(&Listener::init, &this->listener);

    // server_worker.detach();
    listener_worker.detach();

    while(!this -> listener.listening){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        //sleep to not use 100% of cpu
    }


    this -> is_ready.store(true);

    Subnet subnet = util::get_network_address();

    std::vector<in_addr_t> vect = util::get_ip_addrs(subnet);

    std::vector<in_addr_t> responders;
    std::cout << "cat";

    for(in_addr_t addr : vect){
        if(this -> sender.try_conn(addr) == 1){
            responders.push_back(addr);
        }
    }


    std::cout << "responder count" << responders.size() << "\n";
}

// int Network::send(std::string){

//     //file handling portion

// }
