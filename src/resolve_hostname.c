#include "../include/ft_traceroute.h"

void resolve_hostame_and_display(struct sockaddr_in *src_addr, long rtt)
{
    char hostname[NI_MAXHOST]; // NI_MAXHOST standarf POSIX, DNS protocole
    int err = getnameinfo((struct sockaddr*)src_addr, sizeof(src_addr), hostname, sizeof(hostname), NULL, 0, NI_NAMEREQD);

    if (err != 0)
        strcpy(hostname, inet_ntoa(src_addr->sin_addr));

    if (f_packet == 1)
        printf("%s (%s) ", hostname, inet_ntoa(src_addr->sin_addr));
    printf("%ld ms ", rtt); 
}