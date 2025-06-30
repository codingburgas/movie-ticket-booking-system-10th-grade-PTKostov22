#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "update_movie.h"
#include "utils.h"

struct MovieEntry {
    std::string title;
    std::string language;
    std::string genre;
    std::string date;
    std::string showtimes;
};

void updateMovie() {
    std::ifstream inFile("schedule.txt");
    if (!inFile.is_open()) {
        std::cout << "ERROR: Could not open schedule.txt\n";
        pauseScreen();
        return;
    }

    std::vector<MovieEntry> movies;
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        MovieEntry movie;
        std::getline(ss, movie.title, '|');
        std::getline(ss, movie.language, '|');
        std::getline(ss, movie.genre, '|');
        std::getline(ss, movie.date, '|');
        std::getline(ss, movie.showtimes);

        movies.push_back(movie);
    }
    inFile.close();

    if (movies.empty()) {
        std::cout << "No movies found in schedule.\n";
        pauseScreen();
        return;
    }

    std::cout << "Movies in schedule:\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << i + 1 << ". " << movies[i].title << " | "
            << movies[i].language << " | "
            << movies[i].genre << " | "
            << movies[i].date << " | "
            << movies[i].showtimes << "\n";
    }

    std::cout << "\nEnter the number of the movie to update: ";
    int index;
    std::cin >> index;
    std::cin.ignore();

    if (index < 1 || index > movies.size()) {
        std::cout << "Invalid movie number.\n";
        pauseScreen();
        return;
    }

    MovieEntry& movie = movies[index - 1];

    std::cout << "\nWhat would you like to update?\n";
    std::cout << "1. Title\n2. Language\n3. Genre\n4. Date\n5. Showtimes\n";
    std::cout << "Enter choice: ";
    int fieldChoice;
    std::cin >> fieldChoice;
    std::cin.ignore();

    std::string newValue;
    std::cout << "Enter new value: ";
    std::getline(std::cin, newValue);

    switch (fieldChoice) {
    case 1: movie.title = newValue; break;
    case 2: movie.language = newValue; break;
    case 3: movie.genre = newValue; break;
    case 4: movie.date = newValue; break;
    case 5: movie.showtimes = newValue; break;
    default:
        std::cout << "Invalid field.\n";
        pauseScreen();
        return;
    }

    std::ofstream outFile("schedule.txt");
    for (const auto& m : movies) {
        outFile << m.title << "|" << m.language << "|" << m.genre
            << "|" << m.date << "|" << m.showtimes << "\n";
    }
    outFile.close();

    std::cout << "Movie updated successfully.\n";
    pauseScreen();
}
