#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //socket lib
#include <sys/types.h>  //data types used in sockets
#include <netinet/in.h> //structs for domain addresses
#include <arpa/inet.h>  // for modding IP addresses (numeric)
#include <unistd.h>     //to close socket
#include <string.h>     //for memset and strlen

#define SERVER_ADDRESS "98.137.11.164" // yahoo.com
#define PORT 80

int main()
{

    ////////////////////////////////////////////////////////
    // Define necessary information before connection
    ////////////////////////////////////////////////////////

    // declare socket
    int client_socket;

    char server_response[1024]; // this buffer holds the server response

    // this data is the request message string, it lets the server know this is a GET request which asks for a web page
    char *request_data = "GET / HTTP/1.0\r\n\r\n";
    // explanation of data message:
    /*
    GET: requesting to retrieve(GET) data
    / : resource wanted is at root of server
    HTTP/1.0: version of protocol wanted
    \r\n\r\n: first pair - end of request line, second pair - end of headers

    */

    /*
     AF_INET = address family of ipv4
     SOCK_STREAM = define what type of socket to use, this socket should provide a continuous stream of data
     0 = identifier number for the protocol desired, 0 means default protocol, which is TCP

    */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0)
    {

        printf("failed to initialize socket\n");

        return -1;
    }

    // server address struct
    struct sockaddr_in server_address;

    server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); // converts the server address from stringn to network address
    server_address.sin_port = htons(PORT);                      // converts port number from host byte order to network byte order
    server_address.sin_family = AF_INET;                        // address family is of IPV4

    ////////////////////////////////////////////////////////
    // Start connection
    ////////////////////////////////////////////////////////

    // try to connect
    int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connection_status == -1)
    {

        printf("Connection not established, an error occured\n");
        return -1;
    }

    printf("Connection established\n");

    ////////////////////////////////////////////////////////
    // Send and listen for messages
    ////////////////////////////////////////////////////////

    // connection has been established, thus send the request message through the socket
    write(client_socket, request_data, strlen(request_data));

    // clear buffer, just to avoid zombie bytes
    memset(server_response, 0, 1024);

    // listens to server responses, then put server response into buffer
    read(client_socket, server_response, 1023); // exclude null terminator

    // close the connection
    close(client_socket);

    // print server response
    printf("Sever responded with: %s\n ", server_response);

    return 0;
}
