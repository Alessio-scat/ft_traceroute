#include "../include/ft_traceroute.h"

int create_raw_socket()
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sockfd < 0) {
        fprintf(stderr, ERR_CANNOT_CREATE_SOCKET, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

int main ()
{
    int sockfd = create_raw_socket();

    printf("Raw socket (UDP) created successfully\n");

    close(sockfd);
    return 0;
}