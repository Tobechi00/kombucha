#include "headers/network.h"
#include <iostream>

int main(){

    Network network;

    network.init();

    if(network.is_ready){
        std::cout << "network ready \n";
    }


}
