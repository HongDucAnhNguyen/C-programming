#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_ADDRESS "98.137.11.164" //yahoo.com
#define PORT 80

int main(){

//create socket
int network_socket;

network_socket = socket(AF_INET, SOCK_STREAM, 0);

if(network_socket < 0){

printf("failed to initialize socket\n");


return -1;

}

// address struct
struct sockaddr_in server_address;

server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
server_address.sin_port = htons(PORT);
server_address.sin_family = AF_INET;







int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

if(connection_status == -1){


printf("Connection not established, an error occured\n");
return -1;

}
printf("Connection established\n");
char server_response[256];
char *data;
data = "HEAD / HTTP/1.0\r\n\r\n";


write(network_socket, data, strlen(data));
memset(server_response, 0, 256);
read(network_socket, server_response, 255); //exclude null terminator


close(network_socket);

printf("Sever responded with: %s\n ", server_response);

return 0;

}





