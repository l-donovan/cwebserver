#pragma once

#include <string>

#include "Response.h"

#define RECV_BUF_SIZE 2048

void error(const char*);
std::string read_message(int);
void send_message(int, Response);
int create_server(int);
int listen_server(int);
std::string format_string(const char*, ...);
