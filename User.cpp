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
    if (!curl) {
        std::cerr << "curl initialization failure" << std::endl;
        exit(1);
    }
    curl_global_init(CURL_GLOBAL_ALL);          // setup for winsock
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    if (!load_config()) {
        int tries = 0;
        while (login.empty() && tries < 3) {
            std::cout << "Введите имя пользователя (почта): ";
            std::cin >> login;
            ++tries;
        }
        tries = 0;
        while (password.empty() && tries < 3) {
            std::cout << "Введите пароль (почта): ";
            std::cin >> password;
            ++tries;
        }
        std::ofstream config("config.txt");
        config << login << std::endl << password;
        config.close();
        std::cerr << "--Login and password are saved to config.txt--\n";
    } else {
        std::cerr << "--Login and password are imported from config.txt--\n";
    }
}

User::~User() {
    curl_easy_cleanup(curl);
}

bool User::load_config() {
    std::ifstream file_in("config.txt");
    if (file_in.is_open()) {
        file_in >> login >> password;
        if (!login.empty() && !password.empty())
            return true;
    }
    return false;
}

void User::perform_GET_Request(const std::string &link) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curlBuffer.clear();
    if (curl) //проверка
    {
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "CURL perform failed" << std::endl;
    }
}

void User::perform_POST_Request(const std::string &link, std::string &&body) {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

}

bool User::Authenticate_user() {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.adidas.ru/adidasrunners/api/auth/login");

    {   // setup headers for correct CURL request
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers,
                                    "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36");
        headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
        headers = curl_slist_append(headers, "Cookie: onesite_country=RU;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    std::string auth_link = R"({"email":")" + login + R"(","password":")" + password + R"(","adidasMarket":"RU"})";
    const char *data = auth_link.c_str();
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    res = curl_easy_perform(curl);
    std::cout << curlBuffer << std::endl;
    std::cout << res << std::endl;

    if (res == CURLE_OK) {
        std::cout << "Authentication is success" << std::endl;
        return true;
    } else {
        std::cerr << "Authentication is failed\n" << std::endl;
        return false;
    }

}

