#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include "utils.h"

void viewBookings(const std::string& loggedInUserEmail) {
    std::string username = loggedInUserEmail.substr(0, loggedInUserEmail.find('@'));
    std::string filePath = "profiles/" + username + ".txt";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "ERROR: Could not open user profile file.\n";
        pauseScreen();
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::vector<std::pair<int, int>> bookingRanges; // pairs of start and end line indices
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == "Booking:") {
            int start = i;
            int end = i;
            while (++end < lines.size() && lines[end] != "Booking:" && !lines[end].empty());
            bookingRanges.emplace_back(start, end - 1);
            i = end - 1;
        }
    }

    if (bookingRanges.empty()) {
        std::cout << "No bookings found in your profile.\n";
        pauseScreen();
        return;
    }

    std::cout << "\nYour Bookings:\n";
    for (size_t i = 0; i < bookingRanges.size(); ++i) {
        std::cout << "\nBooking #" << i + 1 << ":\n";
        for (int j = bookingRanges[i].first; j <= bookingRanges[i].second; ++j) {
            std::cout << lines[j] << "\n";
        }
    }

    std::cout << "\nDo you want to delete a booking? (Y/N): ";
    char delChoice;
    std::cin >> delChoice;
    std::cin.ignore();

    if (delChoice == 'Y' || delChoice == 'y') {
        std::cout << "Enter the booking number to delete: ";
        int delIndex;
        std::cin >> delIndex;
        std::cin.ignore();

        if (delIndex < 1 || delIndex > bookingRanges.size()) {
            std::cout << "Invalid booking number.\n";
            pauseScreen();
            return;
        }

        auto range = bookingRanges[delIndex - 1];
        lines.erase(lines.begin() + range.first, lines.begin() + range.second + 1);

        std::ofstream out(filePath);
        for (const std::string& l : lines) {
            out << l << "\n";
        }
        out.close();

        std::cout << "Booking deleted successfully.\n";
    }

    pauseScreen();
}
