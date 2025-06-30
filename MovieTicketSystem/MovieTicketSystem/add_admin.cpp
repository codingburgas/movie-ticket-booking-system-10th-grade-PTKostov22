#include "add_admin.h"
#include <iostream>
#include <fstream>
#include <string>

void addAdmin() {
    std::string newAdminEmail;
    std::string newAdminPassword;

    std::cout << "Enter new admin email: ";
    std::getline(std::cin, newAdminEmail);

    std::cout << "Enter new admin password: ";
    std::getline(std::cin, newAdminPassword);

    // Simple validation
    if (newAdminEmail.find('@') == std::string::npos) {
        std::cout << "Invalid email format.\n";
        return;
    }

    std::ofstream adminsFile("users.txt", std::ios::app);
    if (!adminsFile.is_open()) {
        std::cout << "Error opening users.txt file.\n";
        return;
    }

    // Append email,password
    adminsFile << newAdminEmail << "," << newAdminPassword << "\n";
    adminsFile.close();

    std::cout << "Admin added successfully.\n";
}
