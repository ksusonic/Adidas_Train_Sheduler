#ifndef ADIDAS_USER_H
#define ADIDAS_USER_H
#include <iostream>
#include <ctime>
#include "curl/curl.h"

class User {
public:
    User();
    CURL *curl{curl_easy_init()}; // CURL object
    std::string curlBuffer;
    static size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer);
    void setLink(const std::string &link) const;

    void performCurl() const {
        if(curl) //проверка
        {
            curl_easy_perform(curl);
        } else throw std::runtime_error("cURL is not configured");
    }


    ~User();

private:
    char curlErrorBuffer[CURL_ERROR_SIZE];
    time_t end_time = time(nullptr);
    std::string train_name;
    std::string email, password;
    std::string notification_email;
};


#endif //ADIDAS_USER_H
