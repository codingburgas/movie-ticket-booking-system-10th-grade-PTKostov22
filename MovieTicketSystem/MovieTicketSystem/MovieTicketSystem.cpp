#include <iostream>
#include "menu.h"
#include "login.h"

int main() {
    std::string loggedInUserEmail;
    bool isAdmin = false;

    if (login(loggedInUserEmail, isAdmin)) {
        handleMenuChoice(isAdmin);  // ????????? ????? ???
    }
    else {
        std::cout << "Exiting...\n";
    }
    return 0;
}
