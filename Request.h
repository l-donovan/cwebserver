#pragma once

#include <map>
#include <string>

class Request {
    public:
        Request(std::string);
        std::string get_header(std::string);
        std::string get_method();
        std::string get_path();
    private:
        std::string msg;
        std::string method;
        std::string path;
        std::map<std::string, std::string> headers;
};
