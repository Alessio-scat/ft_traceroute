#include "../include/ft_traceroute.h"

/*
    @buffer : small buffer because data is not big. The goal is just to pass the packet through the network, not to send important application information.
*/

int send_udp_packet(int sockfd, struct sockaddr_in *dest_addr, int ttl, int port) {
    socklen_t addr_len = sizeof(*dest_addr);
    char buffer[32];

    dest_addr->sin_port = htons(port);

    // set the value ttl
    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
        perror("setsockopt failed");
        return -1;
    }

    // Send packet UDP
    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)dest_addr, addr_len) < 0) {
        perror("sendto failed");
        return -1;
    }

    return 0;
}