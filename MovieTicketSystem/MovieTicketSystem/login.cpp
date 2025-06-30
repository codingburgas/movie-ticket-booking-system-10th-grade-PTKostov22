#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
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
    std::string email, password;
    const std::string role = "user"; // default role
    const std::string specialChars = "!@#$%^&*()-_=+[]{}|;:',.<>?/";

    while (true) {
        system("cls");
        std::cout << "+---------------------------------------+\n";
        std::cout << "|         Register New Account          |\n";
        std::cout << "+---------------------------------------+\n\n";

        std::cout << "Enter Email: ";
        std::cin >> email;

        // Check for valid email format
        if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
            std::cout << "\nInvalid email format. Email must contain '@' and '.'\n";
            system("pause");
            continue;
        }

        //Check if email contains "admin" (case-insensitive)
        std::string lowerEmail = email;
        std::transform(lowerEmail.begin(), lowerEmail.end(), lowerEmail.begin(), ::tolower);
        if (lowerEmail.find("admin") != std::string::npos) {
            std::cout << "\nError: Cannot register with email containing 'admin'.\n";
            std::cout << "Please choose a different email.\n";
            system("pause");
            continue;
        }

        // Check if email already exists
        std::ifstream infile("users.txt");
        std::string line;
        bool emailExists = false;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string existingEmail;
            std::getline(ss, existingEmail, ',');
            if (existingEmail == email) {
                emailExists = true;
                break;
            }
        }

        if (emailExists) {
            std::cout << "\nEmail already exists. Try logging in.\n";
            system("pause");
            return;
        }

        std::cout << "Enter Password (min 6 chars, 1 uppercase, 1 special char): ";
        std::cin >> password;

        // Check password strength
        bool hasUpper = false, hasSpecial = false;
        for (char ch : password) {
            if (std::isupper(ch)) hasUpper = true;
            if (specialChars.find(ch) != std::string::npos) hasSpecial = true;
        }

        if (password.length() < 6 || !hasUpper || !hasSpecial) {
            std::cout << "\nPassword must be at least 6 characters long,\n";
            std::cout << "and include at least one uppercase letter and one special character.\n";
            system("pause");
            continue;
        }

        // Append new user to users.txt
        std::ofstream outfile("users.txt", std::ios::app);
        if (!outfile.is_open()) {
            std::cout << "ERROR: Could not open users.txt\n";
            system("pause");
            return;
        }
        outfile << email << "," << password << "," << role << "\n";
        outfile.close();

        // Extract username (text before @)
        size_t atPos = email.find('@');
        std::string username = email.substr(0, atPos);

        // Create profiles/ folder if it doesn't exist
#ifdef _WIN32
        system("mkdir profiles >nul 2>&1");
#else
        system("mkdir -p profiles");
#endif

        // Create profile file in profiles/username.txt
        std::string profilePath = "profiles/" + username + ".txt";
        std::ofstream profileFile(profilePath);
        if (profileFile.is_open()) {
            profileFile << "Email: " << email << "\n";
            profileFile << "Role: " << role << "\n";
            profileFile << "Bookings:\n";
            profileFile.close();
        }
        else {
            std::cout << "\nERROR: Could not create profile file.\n";
            system("pause");
            return;
        }

        std::cout << "\nRegistration successful! You can now log in.\n";
        system("pause");
        return;
    }
}

