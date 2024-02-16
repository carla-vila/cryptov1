#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../rsa_algorithm_related/rsa.h" // Adjust the path as necessary

// gcc client_program.c -o client_program
// gcc client_program.c rsa.o -o client_program
// ./client_program  


//#define PORT 8080
//#define SERVER_IP "192.168.1.100" // Replace with the IP address of the server

#define SERVER_IP "127.0.0.1"
#define PORT 12345

// Function to simulate collecting humidity data
double collect_humidity_data() {
    // Simulate collecting humidity data (replace this with actual data collection)
    return rand() % 101; // Return a random value between 0 and 100 for humidity
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    long long public_key = 17; // Example public key
    long long modulus = 6113; // Example modulus

    while (1) {
        // Simulate collecting humidity data
        double humidity = collect_humidity_data();

        // Convert the humidity value to a string
        char data[1024];
        snprintf(data, sizeof(data), "%.2f", humidity);

        // Encrypt the humidity data using RSA encryption
        long long encrypted_data = rsa_encrypt(atoll(data), public_key, modulus);

        // Convert the encrypted data to a string
        char message[1024];
        snprintf(message, sizeof(message), "%lld", encrypted_data);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("connection failed");
            exit(EXIT_FAILURE);
        }

        // Send the encrypted humidity data to the server
        send(sock, message, strlen(message), 0);
        printf("Encrypted humidity data sent: %s\n", message);

        // Close the socket after sending the data
        close(sock);

        // Pause execution for two seconds
        sleep(2);
    }

    return 0;
}