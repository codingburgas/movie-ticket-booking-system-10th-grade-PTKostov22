#include "view_booking.h"
#include <iostream>
#include <fstream>
#include <string>

void viewBookings(const std::string& loggedInUserEmail) {
    std::string username = loggedInUserEmail.substr(0, loggedInUserEmail.find('@'));
    std::string profilePath = "profiles/" + username + ".txt";

    std::ifstream file(profilePath);
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open profile file for user '" << username << "'.\n";
        return;
    }

    std::string line;
    bool inBookingSection = false;

    std::cout << "\nYour Bookings:\n\n";

    while (std::getline(file, line)) {
        if (line.find("Booking:") != std::string::npos) {
            inBookingSection = true;
            std::cout << "-------------------------\n";
            std::cout << line << "\n";
        }
        else if (inBookingSection) {
            if (line.empty()) {
                inBookingSection = false;
                std::cout << "\n";
            }
            else {
                std::cout << line << "\n";
            }
        }
    }

    file.close();
    std::cout << "-------------------------\n";

    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore();
    std::cin.get();
}
