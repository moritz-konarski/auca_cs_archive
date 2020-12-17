/*
 * The structure and code of this file is taken from 
 * https://github.com/auca/com.463/blob/master/client_server_example/client.c
 * the other code is based on the code shown during the lecture on 2020-12-14
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define INPUT_BUFFER_SIZE 1024
#define REPLY_BUFFER_SIZE 10 * 1024 * 1024
static char input[INPUT_BUFFER_SIZE];
static char reply[REPLY_BUFFER_SIZE];

void process_error(char *message) {
    if (message == NULL) {
        // a function to print a descriptive error message
        perror("Error");
    } else {
        fputs(message, stderr);
    }
}

int close_socket(int socket) {
    int result = -1;

    // shutdown the socket (block communication)
    if (-1 == shutdown(socket, SHUT_RDWR)) {
        process_error(NULL);
    } else {
        // actually destroy the socket
        if (-1 == close(socket)) {
            process_error(NULL);
        } else {
            result = 1;
        }
    }
    return result;
}

int main(int argc, char **argv) {
    // socket ID
    int client_socket;

    /*
     * struct that contains
     *  family of the socket
     *  port number
     *  the address itself
     *  and some data that seems redundant, see 
     *      https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
     */
    struct sockaddr_in server_address;

    /*
     * struct that contains host information
     *  host name
     *  host name aliases
     *  host address type
     *  host address length
     *  host addresses
     */
    struct hostent *host_ip_addresses;
    /*
     * the actual address of the server just the IP address
     */
    struct in_addr *host_ip_address;

    // if the wrong number of arguments is supplied
    if (argc != 3) {
        process_error("Usage: nc <host> <port>.\n");
        exit(EXIT_FAILURE);
    }

    // if host info struct retrieval fails
    if (!(host_ip_addresses = gethostbyname(argv[1]))) {
        herror(NULL);
        exit(EXIT_FAILURE);
    }

    // get the IP address from the host info struct, only the first one
    host_ip_address = (struct in_addr *) *(host_ip_addresses->h_addr_list);

    // convert the IP number to an address
    printf("Server IP: %s\n", inet_ntoa(*host_ip_address));

    /* 
     * create a client socket from 
     *  PF_INET     - protocol family INET
     *  SOCK_STREAM - connection based protocol
     *  IPPROTO_TCP - use TCP?
     */
    client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // if socket creation fails
    if (client_socket == -1) {
        process_error(NULL);
        exit(EXIT_FAILURE);
    }

    // set the server address fields to 0
    memset(&server_address, 0, sizeof(server_address));
    // set address family to INET
    server_address.sin_family = AF_INET;
    // set server port from user input
    // htons converts host to network byte order
    server_address.sin_port = htons(atoi(argv[2]));
    // set server IP address
    server_address.sin_addr = *host_ip_address;

    // if the connection fails
    if (-1 == connect(
            client_socket,
            (struct sockaddr *) &server_address,
            sizeof(server_address))
            ) {
        process_error(NULL);
        close_socket(client_socket);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read;
    // read user input bytes 
    while (0 <= (bytes_read = read(0, input, INPUT_BUFFER_SIZE - 4))) {
        // format specifically for HTTP
        input[bytes_read - 1] = '\r';
        input[bytes_read] = '\n';
        input[bytes_read + 1] = '\r';
        input[bytes_read + 2] = '\n';
        input[bytes_read + 3] = '\0';

        // sent message to server
        if (-1 == send(client_socket, input, bytes_read + 4, 0)) {
            process_error(NULL);
            close_socket(client_socket);
            exit(EXIT_FAILURE);
        }

        // set reply buffer to 0
        memset(reply, 0, REPLY_BUFFER_SIZE);

        // receive the message back from the server
        if (-1 == recv(client_socket, reply, REPLY_BUFFER_SIZE, MSG_WAITALL)) {
            process_error(NULL);
            close_socket(client_socket);
            exit(EXIT_FAILURE);
        }

        // print the reply
        printf("\nReply: %s\n", reply);
    }

    // close the socket
    if (-1 == close_socket(client_socket)) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
