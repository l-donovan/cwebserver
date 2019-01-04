/*
 * CWebServer
 * Luke Donovan, 2019
 *
 * TODO
 *  - URL mapping
 *  - Request/response handling
 *  - Logging
 *  - Much, much, more
 *
 */

#pragma once

#include <vector>

class CWebServer {
    public:
        CWebServer();
        CWebServer(int);
        void set_port(int);
        int get_port();
        int startup();
        void shutdown(int);
        int command_loop();
    private:
        int server;
        int portno;
        std::vector<int> clients;
};
