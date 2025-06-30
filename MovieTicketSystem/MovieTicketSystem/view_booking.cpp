#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include "utils.h"
#include "notification.h"

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

    std::vector<std::pair<int, int>> bookingRanges; // start and end line numbers of bookings

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

        // Extract details for notification
        std::string movieTitle = "Unknown";
        std::string cityName = "Unknown";
        std::string cinemaName = "Unknown";
        std::string showtime = "Unknown";

        for (int i = range.first; i <= range.second; ++i) {
            const std::string& l = lines[i];
            if (l.find("Movie: ") == 0) movieTitle = l.substr(7);
            else if (l.find("City: ") == 0) cityName = l.substr(6);
            else if (l.find("Cinema: ") == 0) cinemaName = l.substr(8);
            else if (l.find("Showtime: ") == 0) showtime = l.substr(10);
        }

        // Delete booking
        lines.erase(lines.begin() + range.first, lines.begin() + range.second + 1);

        // Save updated profile
        std::ofstream out(filePath);
        for (const std::string& l : lines) {
            out << l << "\n";
        }
        out.close();

        std::cout << "Booking deleted successfully.\n";

        // Notification
        std::string notifMsg = "Booking canceled for movie '" + movieTitle +
            "' at " + cinemaName + " in " + cityName +
            " on " + showtime + ".";
        showNotification(notifMsg);
    }

    pauseScreen();
}
