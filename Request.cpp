#include "Request.h"

#include <regex>
#include <string>

Request::Request(std::string s) {
    msg = s;

    std::regex reqln_regex("^(\\w+)\\s+(.*)\\s+HTTP\\/1\\.1", std::regex_constants::ECMAScript);
    auto reqln_begin = std::sregex_iterator(msg.begin(), msg.end(), reqln_regex);
    auto reqln_end = std::sregex_iterator();

    for (auto it = reqln_begin; it != reqln_end; ++it) {
        std::smatch match = *it;
        method = match[1].str();
        path = match[2].str();
    }

    std::regex header_regex("\\n(.*?):\\s*(.*)", std::regex_constants::ECMAScript);
    auto header_begin = std::sregex_iterator(msg.begin(), msg.end(), header_regex);
    auto header_end = std::sregex_iterator();

    for (auto it = header_begin; it != header_end; ++it) {
        std::smatch match = *it;
        std::string key = match[1].str(), val = match[2].str();
        headers.insert(std::pair<std::string, std::string>(key, val));
    }
}

std::string Request::get_header(std::string h) {
    auto result = headers.find(h);
    if (result == headers.end()) {
        return NULL;
    } else {
        return result->second;
    }
}

std::string Request::get_method() {
    return method;
}

std::string Request::get_path() {
    return path;
}
