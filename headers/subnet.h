#ifndef SUBNET_H
#define SUBNET_H
#include <netinet/in.h>
typedef struct{
    in_addr_t ip;
    in_addr_t netmask;
}Subnet;

#endif
