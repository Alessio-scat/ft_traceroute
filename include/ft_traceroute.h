#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <sys/time.h>

#define ERR_CANNOT_CREATE_SOCKET "Error: Cannot create raw socket: %s\n"
#define ERR_SOCKET_NOT_PERMITTED "ping: socket: Operation not permitted\n"

extern volatile int running;
extern volatile int f_packet;

/*
    check_root.c
*/
void check_root_privileges();

/*
    icmp.c
*/
int receive_icmp_response(int sockfd, int ttl);

/*
    send_udp.c
*/
int send_udp_packet(int sockfd, struct sockaddr_in *dest_addr, int ttl);

#endif
