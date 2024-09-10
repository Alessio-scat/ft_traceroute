#include "../include/ft_traceroute.h"

volatile int running = 1;

void handle_interrupt(int sig) {
    (void)sig;
    running = 0;
}

int create_raw_socket_udp()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // Changer pour SOCK_DGRAM (UDP)
    if (sockfd < 0) {
        fprintf(stderr, ERR_CANNOT_CREATE_SOCKET, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

int create_raw_socket_icmp()
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);  // Socket pour réception des paquets ICMP
    if (sockfd < 0) {
        fprintf(stderr, ERR_CANNOT_CREATE_SOCKET, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

int main ()
{
    check_root_privileges();
    int udp_sockfd = create_raw_socket_udp();
    int icmp_sockfd = create_raw_socket_icmp();
    printf("Raw socket (UDP) created successfully\n");

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(33434);
    inet_pton(AF_INET, "8.8.8.8", &dest_addr.sin_addr);
    
    int ttl = 1;

    signal(SIGINT, handle_interrupt); 
    while (running)
    {
        // Send UDP packet with ttl actual
        if (send_udp_packet(udp_sockfd, &dest_addr, ttl) < 0)
            break;

        // Receive response message ICMP
        if (receive_icmp_response(icmp_sockfd, ttl) == 1)
            break ;
        
        ttl++;
        sleep(1);
    }


    close(udp_sockfd);
    close(icmp_sockfd);
    return 0;
}