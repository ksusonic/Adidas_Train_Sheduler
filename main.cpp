#include <iostream>
#include "curl/curl.h"

std::string curlBuffer;
size_t curlWriteFunc(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    size_t result = 0;

    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

int main()
{
    std::string readBuffer;
    CURL *curl; //объект типа CURL
    curl = curl_easy_init(); //инициализация
    if(curl) //проверка
    {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.adidas.ru/adidasrunners/community/moscow");

        curl_easy_perform(curl);

        std::cout << curlBuffer; // Просто выводим результат запроса.

        curl_easy_cleanup(curl);
    }
    return 0;
}