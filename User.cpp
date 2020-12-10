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
    curlBuffer.clear();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    if (curl) //проверка
    {
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "CURL perform failed" << std::endl;
    }
}

bool User::Authenticate_user() {
    curlBuffer.clear();
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

    if (res == CURLE_OK) {
        access_token = Parser::Get_token_from_link(curlBuffer);
        if (access_token.empty()) {
            std::cerr << "--Token not found--" << std::endl;
            return false;
        }
        std::cerr << "--Authentication is success--" << std::endl;
        user_logged = true;
//        std::cerr << "token: " + access_token << std::endl;
        return true;
    } else {
        std::cerr << "-!-Authentication is failed-!-\n" << std::endl;
        return false;
    }
}

void User::perform_POST_Request(const std::string &link) {
    curlBuffer.clear();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers,
                                "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36");
    headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
    headers = curl_slist_append(headers, "Cookie: onesite_country=RU;");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    if (access_token.empty()) {
        std::cerr << "No token!" << std::endl;
        exit(1);
    }
    std::string body = R"({"accessToken":")" + access_token + R"(","adidasMarket":"RU"})";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error in POST";
    }
    std::cout << "\nResponse is: " << curlBuffer + '\n' << std::endl;
}

bool User::Signup() {
    curlBuffer.clear();
    std::string link_to_signup = "https://www.adidas.ru/adidasrunners/api/events/" + event_id + "/signup";
    perform_POST_Request(link_to_signup);
    if (curlBuffer == R"({"data":""})") {
        std::cout << " ~ ~ ~ Successfully subscribed! ~ ~ ~\nHave a nice train!";
        exit(0);
    } else if (curlBuffer == "{\"error\":{\"code\":\"error.http.bad_request\",\"message\":\"Maximum number of attendees is reached\"}}") {
        std::cout << "No free places :(" << std::endl;
        return false;
    }
    else {
        std::cout << "Cannot subscribe, try again?" << std::endl;
        return false;
    }
}

void User::EventHandler(const std::string &link) {
    std::string link_api = Parser::Link_to_api(link); // преобразуем в ссылку API
    perform_GET_Request(link_api);
    event_id = std::to_string(Parser::GetEventID(curlBuffer));
}
