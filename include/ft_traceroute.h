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
#include <regex.h>
#include <netdb.h>

#define MAX_HOPS 64
#define LEN_PACKET_IP 40
#define ERR_CANNOT_CREATE_SOCKET "Error: Cannot create raw socket: %s\n"
#define ERR_SOCKET_NOT_PERMITTED "ft_traceroute: socket: Operation not permitted\n"
#define ERR_REGEX_COMPILATION "Error: Could not compile regex for hostname validation.\n"
#define ERR_INVALID_ARGUMENT "Error: Invalid argument `%s` after destination.\n"
#define ERR_NO_DESTINATION "Error: No destination provided.\n"
#define ERR_INVALID_DESTINATION "Error: Invalid destination '%s'. Must be a valid IPv4 address or a FQDN.\n"
#define ERR_CANNOT_RESOLVE_HOSTNAME "ft_traceroute: cannot resolve %s: Unknown host\n"

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

/*
    parsing.c
*/
void parse_command_line(int ac, char **av, char **destination);

#endif
