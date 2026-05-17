#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <sys/_types/_in_addr_t.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include "headers/Listener.h"
#include "headers/subnet.h"
#include "headers/util.h"

//send and recieve mode
// assumes client is already active

void Listener::init(){
    //SOCKSTREAM TCP
    // SOCK_DGRAM UDP

    //socket = ipaddress + port_number
    // various ports do various things
    // returns non negative integer if successful
    // icmp echo request to 224.0.0.1.
    // socket
    // use port 9335
    const int PORT_NUM = 9335;

    Subnet subnet = util::get_network_address();//get subnet

    std::vector<in_addr_t> addr_list = util::get_ip_addrs(subnet);//find all ips

    //add handshake like system

    int listener_socket;//domain, type, protocol 0 means do whatever

    while(true){
        listener_socket = socket(AF_INET, SOCK_STREAM, 0);

        if(listener_socket >= 0){
            break;
        }

        std::cerr << "unable to initialize socket" << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //attempt to reestablish connection
        std::cerr << "attempting to re-initialize socket \n";
    }

    //SET SOC OPT???

    //define Listener address
    sockaddr_in listener_address;
    listener_address.sin_family = AF_INET;//input address family ipv4
    listener_address.sin_port = htons(PORT_NUM);//convert port to network byte order
    listener_address.sin_addr.s_addr = INADDR_ANY;

    //Binding of a socket is done to address and port in order to receive data on this socket
    // assign a name to a socket
    // binding a socket to a port
    int bind_val; ;

    while(true){
        bind_val = bind(listener_socket, (struct sockaddr*)&listener_address, sizeof(listener_address));

        if(bind_val == 0){//successful bind
            break;
        }

        std::cerr << "unable to bind socket to address \n";
        std::cout << "attempting to bind socket \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    std::cout << "socket bound to port successfully \n";

    //listen for connections
    // In simple words, the backlog parameter specifies the number of pending connections the queue will hold.

    //When multiple clients connect to the Listener, the Listener then holds the incoming requests in a queue.
    //The clients are arranged in the queue, and the Listener processes their requests one by one as and when queue-member proceeds.
    //The nature of this kind of connection is called queued connection.



    while(listen(listener_socket, 5) == -1){//only defines the backlog
        std::cerr << "unable to listen on socket";
        std::cout << "re-attempting to listen \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    std::cout << "listening on port "<< PORT_NUM << "... \n";

    this->listening.store(true);


    //understand why null

    // while(true){
    //     int client_socket = accept(listener_socket, nullptr, nullptr);//extracts first connection on queue

    //     if(client_socket < 0){
    //         fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
    //         continue;//retry for next client
    //     }

    //     char buffer[1024] = {0};// 1kb

    //     while(true){
    //         int r = recv(client_socket, buffer, sizeof(buffer), 0);//recieves message from connected socket

    //     }

    //     //if(buff == "conn_request") -> isconn = true;
    //     // listener tells server they're ready, server sends
    //     // last recieved message in a string



    //     // if(r == 0){
    //     //     break;//client discon
    //     // }else if(r < 0){
    //     //     fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
    //     //     break;
    //     // }else{
    //     //     //do someting with buffer
    //     // }
    // }


    //socket, buffer, buffer size, flags
    //
    close(listener_socket);
    //closes a file descriptor

    //be both a client and Listener, Listener in one thread, client in another
}
