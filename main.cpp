#include "User.h"

int main() {
    std::cout << "Welcome to the Adidas training scheduler!" << std::endl << std::endl;

    User user;
    user.Authenticate_user();
//
    std::string link = "https://www.adidas.ru/adidasrunners/community/moscow/event/ar-draft-me-hard-tempo-2?cm_sp=RUNNING_HUB-_-LOGGEDIN-_-AR-DRAFT-ME-HARD-TEMPO-2";
//    while (link.empty()) {
//        std::cout << "Link to signup:" << std::endl << std::endl;
//        std::cin >> link;
//    }

    user.EventHandler(link);
    user.Signup();
//    user.perform_POST_Request("https://www.adidas.ru/adidasrunners/api/events/53092/signup");

    return 0;
}