#ifndef ADIDAS_PARSER_H
#define ADIDAS_PARSER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

class Parser {
public:
    static std::string Link_to_api(const std::string &link) { // преобразует ссылку сайта в ссылку API ADIDAS
        /* input:
         * https://www.adidas.ru/adidasrunners/community/moscow/event/ar-draft-me-hard-tempo-1?cm_sp=RUNNING_HUB-_-MOSCOW-_-AR-DRAFT-ME-HARD-TEMPO-1
         * output:
         * https://www.adidas.ru/adidasrunners/api/events/ar-draft-me-hard-tempo-1
         */
        std::string to_find = "event/";
        auto it_begin = std::search(link.begin(), link.end(), to_find.begin(), to_find.end());
        it_begin = it_begin + 6; // передвинулись с начала event до конца event/...
        auto it_end = std::find(it_begin, link.end(), '?');
        return "https://www.adidas.ru/adidasrunners/api/events/" + std::string(it_begin, it_end);
    }

    static std::vector<int> GetMembersInfo(const std::string &json) {

        int nrAttendees = GetParameterFromJson(json, "nrAttendees");
        int maxAttendees = GetParameterFromJson(json, "maxAttendees");

        std::cout << nrAttendees << ' ' << maxAttendees <<std::endl;
        return {nrAttendees, maxAttendees};
    }

private:
    static int GetParameterFromJson(const std::string &json, std::string s) {
        auto it = std::search(json.begin(), json.end(), s.begin(), s.end());
        it = std::find(it, json.end(), ':'); // iterator on number
        auto it_end = std::find(it++, json.end(), ',');
        std::istringstream is(std::string(it, it_end));
        int num = 0;
        is >> num;
        return num;
    }
};


#endif //ADIDAS_PARSER_H
