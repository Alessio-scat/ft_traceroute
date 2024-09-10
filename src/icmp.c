#include "../include/ft_traceroute.h"

/*
    +---------------------------+
    | En-tête IP (20 octets)     |
    | - Adresse source           |
    | - Adresse destination      |
    | - TTL, Protocole (ICMP)    |
    | - Autres champs            |
    +---------------------------+
    | En-tête ICMP               |
    | - Type ICMP (1 octet)      |
    | - Code ICMP (1 octet)      |
    | - Checksum (2 octets)      |
    +---------------------------+
    | Données ICMP (optionnel)   |
    +---------------------------+
*/

int receive_icmp_response(int sockfd, int ttl) {

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));


    char recv_buffer[512];
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    // Reception message ICMP
    int n = recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&src_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        printf("* * * (TTL: %d)\n", ttl);  // display * if nothing response 
        return -1;
    }

    // Display Ip routeur 
    printf("TTL: %d, Received response from %s\n", ttl, inet_ntoa(src_addr.sin_addr));

    // Extract IP Header
    #ifdef __linux__
        struct iphdr *ip_header = (struct iphdr *)recv_buffer;
        int ip_header_len = ip_header->ihl * 4;
    #elif __APPLE__
        struct ip *ip_header = (struct ip *)recv_buffer;
        int ip_header_len = ip_header->ip_hl * 4;
    #endif

    unsigned char icmp_type = recv_buffer[ip_header_len];

    // unsigned char icmp_type = recv_buffer[20];
    if (icmp_type == 11)// ICMP "Time Exceeded" continue the loop
    {  
        printf("ICMP Time Exceeded from %s\n", inet_ntoa(src_addr.sin_addr));
        return 0; 
    } 
    else if (icmp_type == 3) // ICMP "Port Unreachable"
    {  
        printf("Destination reached from %s\n", inet_ntoa(src_addr.sin_addr));
        return 1;  // stop
    }

    return 0;
}