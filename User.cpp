#include "User.h"

size_t User::curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer) {
    size_t result = 0;
    if (buffer != nullptr)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

User::User() {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
}

User::~User() {
    curl_easy_cleanup(curl);
}

void User::setLink(const std::string &link) const {
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
}
