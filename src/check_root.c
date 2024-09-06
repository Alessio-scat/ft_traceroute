#include "../include/ft_traceroute.h"

void check_root_privileges() {
    if (getuid() != 0) {
        fprintf(stderr, ERR_SOCKET_NOT_PERMITTED);
        exit(EXIT_FAILURE);
    }
}