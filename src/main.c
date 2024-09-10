#include "../include/ft_traceroute.h"

volatile int running = 1;
volatile int f_packet = 1;

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

/*
    getaddrinfo : resolve domain in IP adress
    if it's IP adress he do nothing, just return the IP adress
*/
void config_destination(char *destination, struct sockaddr_in *dest_addr)
{
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;  //IPv4
    hints.ai_socktype = SOCK_DGRAM;  // use UDP packet

    int errcode = getaddrinfo(destination, NULL, &hints, &res);
    if (errcode != 0) {
        fprintf(stderr, ERR_CANNOT_RESOLVE_HOSTNAME, destination);
        exit(EXIT_FAILURE);
    }

    memset(dest_addr, 0, sizeof(struct sockaddr_in));
    dest_addr->sin_family = AF_INET;
    dest_addr->sin_port = htons(33434);
    memcpy(&dest_addr->sin_addr, &((struct sockaddr_in *)res->ai_addr)->sin_addr, sizeof(struct in_addr));

    freeaddrinfo(res);
}

/*
    LEN_PACKET_IP 40 :
        - IP header: 20 bytes.
        - UDP or ICMP header: 8 bytes.
        - Packet data: The rest, which is usually 12 bytes.
*/
int main (int ac, char **av)
{
    char *destination = NULL;
    struct sockaddr_in dest_addr;

    parse_command_line(ac, av, &destination);
    check_root_privileges();
    config_destination(destination, &dest_addr);
    
    int udp_sockfd = create_raw_socket_udp();
    int icmp_sockfd = create_raw_socket_icmp();
    
    int ttl = 1;
    signal(SIGINT, handle_interrupt);
    int stop = 0;

    printf("traceroute to %s (%s), %d hops max, %d byte packets\n", destination, inet_ntoa(dest_addr.sin_addr), MAX_HOPS, LEN_PACKET_IP);
    while (running && ttl <= 64)
    {
        printf("%d  ", ttl);

        f_packet = 1;
        for (int i = 0; i < 3; i++){
            
            // Send UDP packet with ttl actual
            if (send_udp_packet(udp_sockfd, &dest_addr, ttl) < 0)
            {
                stop = 1;
                break;
            }

            // Receive response message ICMP
            if (receive_icmp_response(icmp_sockfd, ttl) == 2){
                stop = 1;
                break ;
            }
            f_packet = 0;
        }
        
        if (stop == 1)
            break;
        printf("\n");
        ttl++;
        sleep(1);
    }


    close(udp_sockfd);
    close(icmp_sockfd);
    return 0;
}