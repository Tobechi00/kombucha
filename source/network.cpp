#include "headers/network.h"
#include "headers/client.h"
#include "headers/server.h"
#include <thread>

void Network::init(){

    std::thread server_worker(&Server::init, &this->server);
    std::thread client_worker(&Client::init, &this->client);

    server_worker.detach();
    client_worker.detach();

    while(!server.listening || !client.is_ready){
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        //sleep to not use 100% of cpu
    }

    this -> is_ready.store(true);;
}
