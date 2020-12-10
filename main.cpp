#include "User.h"
#include "parser.h"

int main() {
    // std::string link = "https://www.adidas.ru/adidasrunners/community/moscow/event/ar-draft-me-hard-tempo-1?cm_sp=RUNNING_HUB-_-MOSCOW-_-AR-DRAFT-ME-HARD-TEMPO-1";
//    std::string link = "https://www.adidas.ru/adidasrunners/community/moscow/event/ar-1905-151?cm_sp=RUNNING_HUB-_-LOGGEDIN-_-AR-1905-151";
    // link = Parser::Link_to_api(link); // преобразуем в ссылку API
    std::string link = "https://www.google.com/";

    User user;
//    user.perform_GET_Request(link);

    // Parser::GetMembersInfo(user.curlBuffer);
    user.Authenticate_user();

    return 0;
}