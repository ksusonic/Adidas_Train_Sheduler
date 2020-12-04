#ifndef ADIDAS_USER_H
#define ADIDAS_USER_H
#include <iostream>
#include <ctime>

class User {
public:
    User() = default;


private:
    time_t end_time = time(nullptr);
    std::string train_name;
    std::string email, password;
    std::string notification_email;
};


#endif //ADIDAS_USER_H
