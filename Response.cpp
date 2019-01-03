#include "Response.h"
#include "utils.h"

Response::Response() {}

Response::Response(std::string b) {
    body = b;
}

void Response::set_body(std::string b) {
    body = b;
}

std::string Response::get_body() {
    return body;
}

void Response::set_status_code(int c) {
    status_code = c;
}

int Response::get_status_code() {
    return status_code;
}

void Response::set_header(std::string h, std::string v) {
    headers.insert(std::pair<std::string, std::string>(h, v));
}

std::string Response::get_header(std::string h) {
    auto result = headers.find(h);
    if (result == headers.end()) {
        return NULL;
    } else {
        return result->second;
    }
}

std::string Response::construct() {
    std::string out;
    std::string header_string;

    for (auto it = headers.begin(); it != headers.end(); it++) {
        header_string += it->first + ": " + it->second + "\r\n";
    }

    out = format_string("HTTP/1.1 %d %s\r\n%s\r\n%s", status_code, "Success", header_string.c_str(), body.c_str());

    return out;
}
