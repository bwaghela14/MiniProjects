#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "Socket failed\n";
        return 1;
    }

    sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server listening on port 8080...\n";

    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    std::cout << "Received from client: " << buffer << std::endl;

    const char *reply = "Hello from server!";
    send(new_socket, reply, strlen(reply), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
