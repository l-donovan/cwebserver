#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <vector>

#include "utils.h"

std::vector<int> clients;
int server, client, portno;
struct sockaddr_in serv_addr, cli_addr;

void INT_handler(int sig) {
    std::cout << std::endl << "- Closing connections and stopping server..." << std::endl;

    std::for_each(clients.begin(), clients.end(), [](int client) -> void {
        close(client);
    });

    close(server);

    std::cout << "- Server stopped" << std::endl;

    exit(0);
}

void *handle_client(void *_args) {
    int *args = (int*)_args;
    int client = args[0];

    std::string request = read_message(client);
    std::cout << "- Received request" << std::endl << request << std::endl;

    send_message(client, "HTTP/1.1 200 Success\r\n\r\nTest response");
    std::cout << "- Sent response" << std::endl;

    close(client);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, INT_handler);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    portno = atoi(argv[1]);
    server = create_server(portno);

    std::cout << "- Listening for connections..." << std::endl;

    while (1) {
        pthread_t th;
        int *args = (int*)malloc(sizeof(int));
        client = listen_server(server);
        std::cout << "- Got connection" << std::endl;
        args[0] = client;
        pthread_create(&th, nullptr, handle_client, args);
        clients.push_back(client);
    }

    INT_handler(0);

    return 0;
}
