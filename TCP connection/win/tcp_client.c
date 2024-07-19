#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from client";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Socket creation error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("Invalid address/ Address not supported \n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed \n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send data to the server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Read response from the server
    int valread = recv(sock, buffer, BUFFER_SIZE, 0);
    if (valread > 0)
    {
        printf("Message from server: %s\n", buffer);
    }
    else
    {
        printf("Recv failed with error: %d\n", WSAGetLastError());
    }

    // Close the socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
