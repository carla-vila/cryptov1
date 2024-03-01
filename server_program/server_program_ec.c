#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include "./algorithms/ec_decryption.h"

//gcc server_program_ec.c ./algorithms/ec_decryption.c -o main_program_ec

#define PORT 12345

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all available network interfaces
    address.sin_port = htons(PORT);

    // Binding socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        // Read data from the socket
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0'; // Ensure the received data is null-terminated
            printf("Received: %s\n", buffer);
            
            // Decrypt the ciphertext using the elliptic curve decryption function
            Point *ciphertext = (Point *)buffer;
            long long decrypted_data = ec_decrypt(*ciphertext);

            // Print the decrypted data
            printf("Decrypted: %lld\n", decrypted_data);
        } else {
            // Handle errors or end of connection
            break;
        }
    }
    return 0;
}

