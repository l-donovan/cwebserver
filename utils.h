#pragma once

#include <string>

#include "Request.h"
#include "Response.h"

#define RECV_BUF_SIZE 2048

void error(const char*);
Request read_message(int);
void send_message(int, Response);
int create_server(int);
int listen_server(int);
std::string format_string(const char*, ...);
