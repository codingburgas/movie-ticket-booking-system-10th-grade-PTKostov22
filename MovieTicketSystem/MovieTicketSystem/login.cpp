#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "login.h"

bool login(std::string& loggedInUserEmail, bool& isAdmin) {
    std::string email, password;
    int attempts = 3;

    while (attempts-- > 0) {
        system("cls"); 

        std::cout << "=========================================\n";
        std::cout << "           Welcome to Movie Ticket       \n";
        std::cout << "                Login System              \n";
        std::cout << "=========================================\n\n";

        std::cout << "Enter Email: ";
        std::cin >> email;
        std::cout << "Enter Password: ";
        std::cin >> password;

        std::ifstream file("users.txt");
        if (!file.is_open()) {
            std::cout << "\nERROR: Could not open users.txt file.\n";
            return false;
        }

        std::string line;
        bool found = false;

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string fileEmail, filePassword, role;

            getline(ss, fileEmail, ',');
            getline(ss, filePassword, ',');
            getline(ss, role, ',');

            if (email == fileEmail && password == filePassword) {
                loggedInUserEmail = email;
                isAdmin = (role == "admin");
                std::cout << "\nLogin successful! Welcome, " << (isAdmin ? "Admin" : "User") << "!\n";
                system("pause");
                return true;
            }
        }

        std::cout << "\nInvalid email or password. Attempts left: " << attempts << "\n";
        if (attempts > 0) {
            std::cout << "Please try again.\n";
            system("pause");
        }
    }

    std::cout << "\nToo many failed attempts. Exiting...\n";
    system("pause");
    return false;
}
