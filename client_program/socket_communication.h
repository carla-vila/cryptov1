#ifndef SOCKET_COMMUNICATION_H
#define SOCKET_COMMUNICATION_H

int connect_to_server(const char *server_ip, int port);
void send_data(int socket_fd, const char *data);
void close_connection(int socket_fd);
void send_encrypted_data(long long encrypted_data);

#endif 