#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool movieExists(const std::string& title) {
    std::ifstream file("schedule.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string existingTitle;
        std::getline(ss, existingTitle, '|');

        if (existingTitle == title) {
            return true;
        }
    }
    return false;
}

void addMovieToSchedule() {
    std::string title, language, genre, date, showtimes;

    std::cin.ignore(); // in case something is left in the buffer
    std::cout << "Enter movie title: ";
    std::getline(std::cin, title);

    if (movieExists(title)) {
        std::cout << "A movie with this title already exists in the schedule.\n";
        return;
    }

    std::cout << "Enter language: ";
    std::getline(std::cin, language);

    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    std::cout << "Enter release date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Enter showtimes separated by commas (e.g., 14:00,18:00,21:00): ";
    std::getline(std::cin, showtimes);

    std::ofstream file("schedule.txt", std::ios::app);
    if (file.is_open()) {
        file << title << "|" << language << "|" << genre << "|" << date << "|" << showtimes << "\n";
        file.close();
        std::cout << "Movie added successfully to the schedule.\n";
    }
    else {
        std::cout << "ERROR: Could not open schedule.txt for writing.\n";
    }
}