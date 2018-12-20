#pragma once

#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define RECV_BUF_SIZE 2048

void error(const char *msg) {
    perror(msg);
    exit(1);
}

std::string read_message(int sockfd) {
    char buf[RECV_BUF_SIZE];

    int len = recv(sockfd, buf, RECV_BUF_SIZE - 1, 0);
    buf[len] = 0;

    return std::string(buf);
}

void send_message(int sockfd, std::string msg) {
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
