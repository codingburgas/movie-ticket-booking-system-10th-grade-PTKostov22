#include <iostream>
#include "menu.h" // Include the header
#include "login.h"

int main() {
    std::cout << "Calling login() from main()\\n"; // Added
    if (login()) {
        std::cout << "login() returned true, calling handleMenuChoice()\\n"; // Added
        handleMenuChoice();
        std::cout << "handleMenuChoice() returned\\n"; // Added
    }
    else {
        std::cout << "login() returned false, exiting\\n"; // Added
    }
    std::cout << "Exiting main()\\n"; // Added
    return 0;
}