#include <iostream>
#include <string>
#include "login.h"

bool login() {
    std::string username;
    std::string password;
    int attempts = 3;

    std::cout << "\n";
    std::cout << "  +-----------------------------------------+\n";
    std::cout << "  |          Login to Movie Ticket          |\n";
    std::cout << "  |                 System                  |\n";
    std::cout << "  +-----------------------------------------+\n";
    std::cout << "  |                                         |\n";
    std::cout << "  |  Username:                              |\n";
    std::cout << "  |  Password:                              |\n";
    std::cout << "  |                                         |\n";
    std::cout << "  +-----------------------------------------+\n";

    while (attempts > 0) {
        // Use a loop to get username and password
        std::cout << "\033[F\033[K"; // Move cursor up and erase line
        std::cout << "\033[F\033[K";
        std::cout << "  |  Username: ";
        std::cin >> username;
        std::cout << "\033[F\033[K"; // Move cursor up and erase line
        std::cout << "  |  Password: ";
        std::cin >> password; // In a real application, use secure input

        // Basic authentication (replace with your actual authentication logic)
        if (username == "user" && password == "password") { // Hardcoded for demonstration
            std::cout << "\n  +-----------------------------------------+\n";
            std::cout << "  |          Login successful!              |\n";
            std::cout << "  +-----------------------------------------+\n";
            return true;
        }
        else {
            attempts--;
            std::cout << "\n  +-----------------------------------------+\n";
            std::cout << "  |  Invalid credentials. Attempts remaining:  |\n";
            std::cout << "  |                 " << attempts << "                               |\n";
            std::cout << "  +-----------------------------------------+\n";
            if (attempts > 0) {
                std::cout << "  |  Please try again.                       |\n";
                std::cout << "  +-----------------------------------------+\n";
            }
        }
    }
    std::cout << "\n  +-----------------------------------------+\n";
    std::cout << "  |          Login failed. Exiting.           |\n";
    std::cout << "  +-----------------------------------------+\n";
    return false;
}