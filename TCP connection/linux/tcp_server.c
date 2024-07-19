#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 4444 // server listens on this port

int main()
{

    // create socket
    int client_socket, server_socket;
    char request_buffer[1024];
    char *response = "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\n\r\nHello from server!\n";

    struct sockaddr_in server_address, client_address;

    // clearing buffers
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    // needed by the accept function to know how much memory to allocate for the incoming client's address information.
    socklen_t client_addr_len = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        printf("server socket failed to initialize\n");
        return -1;
    }
    printf("server socket created\n");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = 0;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {

        printf("binding server socket failed\n");
        close(server_socket);
        return -1;
    }
    printf("server socket binded successfully\n");
    // listen marks the socket as a passive socket, which means a socket who receives incoming connection requests
    // the arbitrary number denotes the maximum connections it can queue, in this case a max of 3 pending connections
    if (listen(server_socket, 3) < 0)
    {

        printf("listen failed\n");
        close(server_socket);
        return -1;
    }

    printf("listening on %d...\n", PORT);

    // accept() returns the client socket connection
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
    if (client_socket < 0)
    {
        printf("accept failed\n");
        close(server_socket);
        return -1;
    }
    printf("accepting incoming connections...\n");

    // Read data from client connection into request_buffer as client request data
    read(client_socket, request_buffer, 1024);

    // show contents of request
    printf("Received request:\n%s\n", request_buffer);

    // Send a response to the client
    write(client_socket, response, strlen(response));
    printf("Response sent\n");

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
