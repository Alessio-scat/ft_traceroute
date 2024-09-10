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

long calculate_time_diff(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    return (seconds * 1000) + (microseconds / 1000);
}

int receive_icmp_response(int sockfd, int ttl) {

    (void)ttl;
    struct timeval timeout, start, end;;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));


    char recv_buffer[512];
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    // Reception message ICMP
    gettimeofday(&start, NULL);
    int n = recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&src_addr, &addr_len);
    gettimeofday(&end, NULL);
    if (n < 0) {
        printf("* ");  // display * if nothing response 
        return -1;
    }

    // Display Ip routeur 
    // printf("TTL: %d, Received response from %s\n", ttl, inet_ntoa(src_addr.sin_addr));

    long rtt = calculate_time_diff(start, end);

    // Extract IP Header
    #ifdef __linux__
        struct iphdr *ip_header = (struct iphdr *)recv_buffer;
        int ip_header_len = ip_header->ihl * 4;
    #elif __APPLE__
        struct ip *ip_header = (struct ip *)recv_buffer;
        int ip_header_len = ip_header->ip_hl * 4;
    #endif

    unsigned char icmp_type = recv_buffer[ip_header_len];
    unsigned char icmp_code = recv_buffer[ip_header_len + 1];

    resolve_hostame_and_display(&src_addr, rtt);

    // unsigned char icmp_type = recv_buffer[20];
    if (icmp_type == 11 && icmp_code == 0)// ICMP "Time Exceeded" continue the loop
        return 0; 
    else if (icmp_type == 3 && icmp_code == 3) // ICMP "Port Unreachable"
        return 2;  // stop

    return 0;
}