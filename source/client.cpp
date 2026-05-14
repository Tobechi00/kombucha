#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include "headers/client.h"

void Client::init(){
    //client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    const int PORT_NUM = 9335;

    //define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;//input address family ipv4
    server_address.sin_port = htons(PORT_NUM);//convert port to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY;

    //connect to server

    while(connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){

        std::cerr << "unable to establish a connection connect \n";
        std::cout << "reattempting connection \n";

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    std::cout << "recieving on port " << PORT_NUM << "\n";
    this->is_ready.store(true);

    while(true){//continually accept input from users
        std::string message;
        std::cin >> message;

        const char* char_rep = message.c_str();

        int s_val = send(client_socket, char_rep, strlen(char_rep), 0);
        //sval is the size of the message sent in bytes or -1 if err
    }

    close(client_socket);
}
