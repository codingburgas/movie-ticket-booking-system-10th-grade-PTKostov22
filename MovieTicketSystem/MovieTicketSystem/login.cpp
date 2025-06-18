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

        std::cout << "+---------------------------------------+\n";
        std::cout << "|       Welcome to Movie Ticket         |\n";
        std::cout << "|            Login System               |\n";
        std::cout << "+---------------------------------------+\n\n";

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

void registerUser() {
    std::string email, password, role;

    system("cls");
    std::cout << "+---------------------------------------+\n";
    std::cout << "|         Register New Account          |\n";
    std::cout << "+---------------------------------------+\n\n";

    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;
    std::cout << "Enter Role (admin/user): ";
    std::cin >> role;

    std::ifstream infile("users.txt");
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string existingEmail;
        getline(ss, existingEmail, ',');
        if (existingEmail == email) {
            std::cout << "\nEmail already exists. Please try logging in.\n";
            system("pause");
            return;
        }
    }

    std::ofstream outfile("users.txt", std::ios::app);
    if (!outfile.is_open()) {
        std::cout << "\nERROR: Could not open users.txt to write.\n";
        system("pause");
        return;
    }

    outfile << email << "," << password << "," << role << "\n";
    std::cout << "\nRegistration successful! You can now log in.\n";
    system("pause");
}
