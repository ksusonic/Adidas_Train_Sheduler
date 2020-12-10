#include "User.h"

size_t User::curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer) {
    size_t result = 0;
    if (buffer != nullptr) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

User::User() {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer);
}

User::~User() {
    curl_easy_cleanup(curl);
}

void User::setLink(const std::string &link) const {
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
}

void User::performCurl() const {
    if (curl) //проверка
    {
        CURLcode res;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "CURL perform failed" << endl;
    }
}

void User::setLoginPassword(std::string &&login_, std::string &&password_) {
    login = move(login_);
    password = move(password_);
    curl_easy_setopt(curl, CURLOPT_USERNAME, &login);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, &password);
}

int User::load_congig() {
    con
}
