#include"dependencies.h"
#include<string.h>
int main() {
    int sock = 0;
    struct sockaddr_in server_addr;
    char *get_req = "GET 1.1\r\n";
    char buffer[256] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // Send a message to the server
    send(sock, get_req, strlen(get_req), 0);

    printf("Hello message sent\n");

    // Receive a message from the server
    int valread = recv(sock, buffer, 256, 0);
    if (valread < 0) {
        perror("Read error");
        close(sock);
        return -1;
    }
    printf("Message from server: %s\n", buffer);

    // Close the socket
    close(sock);
    return 0;
}

