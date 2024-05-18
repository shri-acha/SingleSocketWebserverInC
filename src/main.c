#include "dependencies.h"
void* handle_client(void* client_fd);
void send_mssg(int client_fd, const char* message);

int main() {
    int server_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error occurred in starting the socket");
        exit(EXIT_FAILURE);
    }
printf("Server socket initialized with TCP STREAM IN IPv4!\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failure");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
printf("Server File Descriptor binded with server_sock_address!\n");
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

//Listen doesn't actually run in a infinite loop but what actually does is the acceptance.
//In other frameworks like express.js,it is made to think otherwise.
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int* client_fd = malloc(sizeof(int));
        if (client_fd == NULL) {
            perror("Memory allocation failure");
            continue;
        }

        *client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
	//Accept accepts any external requests to the server_file_descriptor by the client address
        if (*client_fd < 0) {
            perror("Error in accepting connection");
            free(client_fd);
            continue;
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)client_fd) != 0) {
            perror("Thread creation failed");
            free(client_fd);
            continue;
        }

        // Detach thread to allow independent execution
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}

void* handle_client(void* client_fd_ptr) {
    int client_fd = *(int*)client_fd_ptr;
    free(client_fd_ptr);

    char buffer[256] = {0};
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    
    if (bytes_received < 0) {
        perror("Error in receiving message");
        close(client_fd);
        return NULL;
    }

    printf("Message received: %s\n", buffer);

    // Respond to the client
    send_mssg(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>\r\n");
	sleep(1);
    close(client_fd);
    return NULL;
}

void send_mssg(int client_fd, const char* message) {
    if (send(client_fd, message, strlen(message), 0) < 0) {
        perror("Error sending message");
    } else {
        printf("Message sent to client\n");
    }
}

