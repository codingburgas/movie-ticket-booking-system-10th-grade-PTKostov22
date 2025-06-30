 #include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
};

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void searchMovies() {
    std::ifstream file("movies.txt");

    if (!file.is_open()) {
        std::cout << "ERROR: Could not open movies.txt\n";
        system("pause");
        return;
    }

    std::vector<Movie> movies;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, language, genre, releaseDate;

        std::getline(ss, title, '|');
        std::getline(ss, language, '|');
        std::getline(ss, genre, '|');
        std::getline(ss, releaseDate);

        title = trim(title);
        language = trim(language);
        genre = trim(genre);
        releaseDate = trim(releaseDate);

        movies.push_back({ title, language, genre, releaseDate });
    }

    int choice;
    std::string query;

    std::cout << "\nSearch by:\n";
    std::cout << "1. Title\n";
    std::cout << "2. Language\n";
    std::cout << "3. Genre\n";
    std::cout << "4. Release Date (Year)\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::cout << "Enter search query: ";
    std::getline(std::cin, query);
    query = trim(query);

    std::vector<Movie> results;

    for (const auto& movie : movies) {
        std::string year = movie.releaseDate.substr(0, 4);

        switch (choice) {
        case 1:
            if (toLower(movie.title).find(toLower(query)) != std::string::npos)
                results.push_back(movie);
            break;
        case 2:
            if (toLower(movie.language).find(toLower(query)) != std::string::npos)
                results.push_back(movie);
            break;
        case 3:
            if (toLower(movie.genre).find(toLower(query)) != std::string::npos)
                results.push_back(movie);
            break;
        case 4:
            if (year == query)
                results.push_back(movie);
            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
        }
    }

    std::cout << "\nSearch Results:\n";
    if (results.empty()) {
        std::cout << "No matching movies found.\n";
    }
    else {
        for (const auto& m : results) {
            std::cout << m.title << " | " << m.language << " | " << m.genre << " | " << m.releaseDate << "\n";
        }
    }

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
}
