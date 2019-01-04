#include "CWebServer.h"
#include "Request.h"
#include "Response.h"
#include "utils.h"

#include <algorithm>
#include <iostream>
#include <signal.h>
#include <thread>
#include <unistd.h>
#include <vector>

CWebServer::CWebServer() {}

CWebServer::CWebServer(int p) {
    portno = p;
}

void CWebServer::set_port(int p) {
    portno = p;
}

int CWebServer::get_port() {
    return portno;
}

void CWebServer::shutdown(int sig) {
    std::cout << std::endl << "- Closing connections and stopping server..." << std::endl;

    std::for_each(clients.begin(), clients.end(), [](int client) -> void {
        close(client);
    });

    close(server);

    std::cout << "- Server stopped" << std::endl;
}

void handle_client(int client) {
    Request request = read_message(client);
    std::cout << "- Requested path: " << request.get_path() << std::endl;
    std::cout << "- Request method: " << request.get_method() << std::endl;

    Response response("Test response");
    response.set_status_code(200);
    response.set_header("Access-Control-Allow-Origin", "*");
    send_message(client, response);
    std::cout << "- Sent response" << std::endl << response.construct() << std::endl;

    close(client);
}

void handle_listener(int server, std::vector<int> *clients) {
    while (1) {
        int client = listen_server(server);
        std::cout << "- Got connection" << std::endl;
        std::thread client_thread(handle_client, client);
        client_thread.detach();
        clients->push_back(client);
    }
}

int CWebServer::startup() {
    server = create_server(portno);

    std::cout << "- Server started. Ctrl-c to exit" << std::endl;
    std::cout << "- Listening for connections..." << std::endl;

    std::thread listener_thread(handle_listener, server, &clients);

    listener_thread.detach();

    return 0;
}

int CWebServer::command_loop() {
    int n;
    while (n != 9) {
        std::cout << "> ";
        std::cin >> n;
    }
    return 0;
}
