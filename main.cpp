#include <iostream>
#include <exception>
#include "curl/curl.h"
#include "parser.h"

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

int main() {
    std::string link = "https://www.adidas.ru/adidasrunners/community/moscow/event/ar-draft-me-hard-tempo-1?cm_sp=RUNNING_HUB-_-MOSCOW-_-AR-DRAFT-ME-HARD-TEMPO-1";
//    std::cin >> link; // for DEBUG
    link = Parser::Link_to_api(link); // преобразуем в ссылку API

    std::string readBuffer;
    CURL *curl; //объект типа CURL
    curl = curl_easy_init(); //инициализация
    if(curl) //проверка
    {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());

        curl_easy_perform(curl);

        Parser::GetMembersInfo(curlBuffer);

        curl_easy_cleanup(curl);
    }
    return 0;
}