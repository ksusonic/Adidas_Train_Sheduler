#include "User.h"
#include "parser.h"

int main() {
    std::string link = "https://www.adidas.ru/adidasrunners/community/moscow/event/ar-draft-me-hard-tempo-1?cm_sp=RUNNING_HUB-_-MOSCOW-_-AR-DRAFT-ME-HARD-TEMPO-1";
    link = Parser::Link_to_api(link); // преобразуем в ссылку API

    User user;
    user.setLink(link);

    user.performCurl();

    Parser::GetMembersInfo(user.curlBuffer);
    std::cout << user.curlBuffer;
    return 0;
}