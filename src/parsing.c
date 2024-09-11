#include "../include/ft_traceroute.h"

void print_help()
{
	printf("Usage: ft_traceroute [OPTION...] HOST ...\n"
	       "Send UDP packets to network hosts.\n\n"
	       " Options:\n"
	       "  -h or -?           Show help\n");
        
    exit(EXIT_SUCCESS);
}

/*
    1 : Ip ok
    0 : Ip invalid
    -1 : error
*/

int is_valid_ipv4(const char *ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip, &(sa.sin_addr));

    if (result == 1)
        return 1; // IP valid
    else
        return 0;
}

int is_valid_hostname(const char *hostname) {

    // Regular expression for validating FQDNs

    const char *regex_pattern = "^[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(\\.[a-zA-Z0-9]([a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$";
    regex_t regex;
    int ret;
    ret = regcomp(&regex, regex_pattern, REG_EXTENDED);

    if (ret) {
        fprintf(stderr, ERR_REGEX_COMPILATION);
        exit(EXIT_FAILURE);
    }

    ret = regexec(&regex, hostname, 0, NULL, 0);
    regfree(&regex);
    
    if (ret == 0)
        return 1;
    else
        return 0;

}

void parse_command_line(int ac, char **av, char **destination) {
    int opt;
    int destination_set = 0;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-') {
            opt = av[i][1];
            switch (opt) {
                case 'h':
                    print_help();
                    break;

                default:
                    print_help();
                    exit(EXIT_FAILURE);
            }
        } else if (!destination_set) {
            *destination = av[i];
            destination_set = 1;
        } else {
            fprintf(stderr, ERR_INVALID_ARGUMENT, av[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (!destination_set) {
        fprintf(stderr, ERR_NO_DESTINATION);
        print_help();
    }

    // Validate the destination

    if (is_valid_ipv4(*destination) == 1) {} 
    else if (is_valid_hostname(*destination) == 1) {} 
    else {
        fprintf(stderr, ERR_INVALID_DESTINATION, *destination);
        exit(EXIT_FAILURE);
    }
}