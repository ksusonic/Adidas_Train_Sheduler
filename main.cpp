#include "User.h"
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
    std::cout << "Welcome to the Adidas training scheduler!" << std::endl << std::endl;

    User user;
    user.Authenticate_user();

    std::cout << "https://www.adidas.ru/adidasrunners/\n"
                 "Insert the interesting train link from the website above\n";
    std::string link;
    while (link.empty()) {
        std::cout << "Your link to signup: ";
        std::cin >> link;
    }

    user.EventHandler(link);
    if (!user.Signup()) {
        int minutes = 0;
        std::cout << "\nHow many minutes do you want to try to attend? (0 if exit)" << std::endl;
        std::cin >> minutes;
        if (minutes > 0)
            for (int i = 0; i <= minutes; ++i) {
                time_t raw_time;
                time(&raw_time);
                std::cout << std::string(5, '-') << ctime(&raw_time) << std::endl;
                user.Signup();
                std::cout << "Okay, wait..." << std::endl;
                sleep(60);
            }
    }

    return 0;
}