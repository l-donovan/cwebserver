#include "CWebServer.h"
#include <signal.h>

#include <iostream>

CWebServer server;

void stop_everything(int sig) {
    server.shutdown(sig);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, stop_everything);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    server.set_port(atoi(argv[1]));

    server.startup();
    server.command_loop();
    server.shutdown(0);
}
