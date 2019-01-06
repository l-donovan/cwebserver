#include "Request.h"
#include "utils.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

Request read_message(int sockfd) {
    char buf[RECV_BUF_SIZE];

    int len = recv(sockfd, buf, RECV_BUF_SIZE - 1, 0);
    buf[len] = 0;
    
    return Request(std::string(buf));
}

void send_message(int sockfd, Response response) {
    std::string msg = response.construct();
    char buf[msg.length()];
    strcpy(buf, msg.c_str());
    if (send(sockfd, buf, msg.length(), 0) < 0) {
        error("ERROR writing to socket");
    }
}

int create_server(int portno) {
    int reuse = 1;
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, (char*)&reuse, sizeof(reuse));
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    return sockfd;
}

int listen_server(int sockfd) {
    int newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    return newsockfd;
}

// This function shamelessly stolen from `https://codereview.stackexchange.com/q/187183`
// Thanks, Toby
std::string format_string(const char *fmt, ...) {
    char buf[256];

    va_list args;
    va_start(args, fmt);
    const auto r = std::vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);

    if (r < 0) {
        return {};
    }

    const size_t len = r;
    if (len < sizeof buf) {
        return {buf, len};
    }

    std::string s(len, '\0');
    va_start(args, fmt);
    std::vsnprintf(const_cast<char*>(s.data()), len + 1, fmt, args);
    va_end(args);

    return s;
}
