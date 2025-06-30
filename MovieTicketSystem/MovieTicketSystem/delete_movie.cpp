#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

void deleteMovie() {
    std::ifstream inFile("schedule.txt");
    if (!inFile.is_open()) {
        std::cout << "ERROR: Could not open schedule.txt\n";
        return;
    }

    std::vector<std::string> lines;
    std::vector<std::string> movieTitles;
    std::string line;

    // Read all lines and extract movie titles
    while (std::getline(inFile, line)) {
        lines.push_back(line);
        std::stringstream ss(line);
        std::string title;
        std::getline(ss, title, '|');  // Extract title before first '|'
        movieTitles.push_back(title);
    }
    inFile.close();

    if (movieTitles.empty()) {
        std::cout << "No movies found in schedule.\n";
        return;
    }

    // Display the list of movies
    std::cout << "Movies in Schedule:\n";
    for (size_t i = 0; i < movieTitles.size(); ++i) {
        std::cout << i + 1 << ". " << movieTitles[i] << "\n";
    }

    std::cout << "Enter the number of the movie to delete: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice < 1 || choice > static_cast<int>(movieTitles.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Remove the selected movie line
    lines.erase(lines.begin() + (choice - 1));

    // Rewrite the file without the deleted movie
    std::ofstream outFile("schedule.txt");
    if (!outFile.is_open()) {
        std::cout << "ERROR: Could not open schedule.txt for writing.\n";
        return;
    }
    for (const std::string& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    std::cout << "Movie deleted successfully.\n";
}
