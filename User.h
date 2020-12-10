#ifndef ADIDAS_USER_H
#define ADIDAS_USER_H
#include <iostream>
#include <fstream>
#include <ctime>
#include "curl/curl.h"

class User {
public:
    User();

    CURL *curl{curl_easy_init()}; // CURL object automatically initialised
    std::string curlBuffer{};       // buffer of Curl responses

    static size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer); // function that writes to curlBuffer

    bool Authenticate_user();
    void perform_GET_Request(const std::string &link);
    void perform_POST_Request(const std::string &link, std::string&& body = "");

    ~User();

private:
    bool user_logged {false};
    bool load_config();
    std::string access_token{};

    CURLcode res;

    time_t end_time = time(nullptr);
    std::string login, password;
};

#endif //ADIDAS_USER_H
