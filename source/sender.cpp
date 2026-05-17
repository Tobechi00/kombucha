#include "headers/sender.h"
#include <cstring>
#include <sys/_types/_in_addr_t.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

void Sender::init(){



    // while(true){//continually accept input


    //     const char* char_rep = "con_req";

    //     int s_val = send(sender_socket, char_rep, strlen(char_rep), 0);



    //     //sval is the size of the message sent in bytes or -1 if err
    // }

    // close(sender_socket);
}

int Sender::try_conn(in_addr_t address){
    //Sender socket
    int sender_socket = socket(AF_INET, SOCK_STREAM, 0);
    const int PORT_NUM = 9335;

    //https://man7.org/linux/man-pages/man2/F_SETFL.2const.html
    //YESSSS
    fcntl(sender_socket, F_SETFL, O_NONBLOCK);

    //define server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;//input address family ipv4
    server_address.sin_port = htons(PORT_NUM);//convert port to network byte order
    server_address.sin_addr.s_addr = address;

    //connect to server
    int conn = connect(sender_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    if(conn == -1){
        return conn;//on to the next;
    }

    std::cerr << "connection established \n";
    // std::cout << "reattempting connection \n";

        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));


    std::cout << "sending to port " << PORT_NUM << "\n";
    // this->is_ready.store(true);
    return 1;
}
