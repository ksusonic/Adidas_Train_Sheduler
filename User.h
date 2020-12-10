#ifndef ADIDAS_USER_H
#define ADIDAS_USER_H
#include <fstream>
#include "curl/curl.h"
#include "parser.h"


class User {
public:
    User();

    CURL *curl{curl_easy_init()}; // CURL object automatically initialised
    std::string curlBuffer{};       // buffer of Curl responses

    static size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer); // function that writes to curlBuffer

    void EventHandler(const std::string &link);
    bool Authenticate_user();
    bool Signup();

    void perform_GET_Request(const std::string &link);
    void perform_POST_Request(const std::string &link);

    ~User();

private:
    bool user_logged {false};
    std::string access_token{};
    CURLcode res;

    bool load_config();
    std::string login, password, event_id;
};

#endif //ADIDAS_USER_H
