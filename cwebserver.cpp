#include "Response.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <vector>

std::vector<int> clients;
int server, client, portno;

void shutdown(int sig) {
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

    // TODO abstract request to a `Request` class
    std::string request = read_message(client);
    std::cout << "- Received request" << std::endl << request << std::endl;

    Response response("Test response");
    response.set_status_code(200);
    response.set_header("Access-Control-Allow-Origin", "*");
    send_message(client, response);
    std::cout << "- Sent response" << std::endl << response.construct() << std::endl;

    close(client);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, shutdown);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    portno = atoi(argv[1]);
    server = create_server(portno);
    std::cout << "- Server started. Ctrl-c to exit" << std::endl;

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

    shutdown(0);

    return 0;
}
