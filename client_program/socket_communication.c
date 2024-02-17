#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "192.168.1.36"

void send_encrypted_data(long long encrypted_data) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[1024];

    // Convert the encrypted data to a string
    snprintf(message, sizeof(message), "%lld", encrypted_data);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Send the encrypted data to the server
    send(sock, message, strlen(message), 0);
    printf("Encrypted data sent: %s\n", message);

    close(sock);
}
