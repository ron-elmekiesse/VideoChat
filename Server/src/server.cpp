#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <pthread.h>
#include <unistd.h>
#include <cerrno>
#include <cctype>
#include <thread>


#define PORT 8080


int main(int argc, char const *argv[]) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if (0 == (server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        std::cout << "ERROR!!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        std::cout << "ERROR!!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address))
        < 0) {
        std::cout << "ERROR!!!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        std::cout << "ERROR!!!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if ((new_socket
                 = accept(server_fd, (struct sockaddr *) &address,
                          (socklen_t *) &addrlen))
        < 0) {
        std::cout << "ERROR!!!" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (1) {
        read(new_socket, buffer, 1024);
        std::cout << buffer << std::endl;
        send(new_socket, "Hello, World!", strlen("Hello, World!"), 0);
    }


    close(new_socket);
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
