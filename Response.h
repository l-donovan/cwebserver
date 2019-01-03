#pragma once

#include <map>
#include <string>

class Response {
    public:
        Response();
        Response(std::string);
        void set_body(std::string);
        std::string get_body();
        void set_status_code(int);
        int get_status_code();
        void set_header(std::string, std::string);
        std::string get_header(std::string);
        std::string construct();
    private:
        std::string body;
        std::map<std::string, std::string> headers;
        int status_code;
};
