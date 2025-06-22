#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <algorithm> 

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
};

void displayMovie(const Movie& movie) {
    std::cout << "Title: " << movie.title << "\n";
    std::cout << "Language: " << movie.language << "\n";
    std::cout << "Genre: " << movie.genre << "\n";
    std::cout << "Release Date: " << movie.releaseDate << "\n";
    std::cout << "----------------------------------------\n";
}

std::vector<Movie> loadMovies(const std::string& filename) {
    std::vector<Movie> movies;
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, language, genre, releaseDate;

        getline(ss, title, '|');
        getline(ss, language, '|');
        getline(ss, genre, '|');
        getline(ss, releaseDate, '|');

        movies.push_back({title, language, genre, releaseDate});
    }

    return movies;
}

void searchMovies() {
    std::vector<Movie> movies = loadMovies("movies.txt");
    if (movies.empty()) {
        std::cout << "No movies found in the list.\n";
        return;
    }

    int choice;
    std::string query;
    std::vector<Movie> results;

    std::cout << "\nSearch by:\n";
    std::cout << "1. Title\n";
    std::cout << "2. Language\n";
    std::cout << "3. Genre\n";
    std::cout << "4. Release Date\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(); // clear newline character

    std::cout << "Enter search query: ";
    getline(std::cin, query);

    std::string lowerQuery = toLower(query);

    for (const auto& movie : movies) {
        switch (choice) {
            case 1:
                if (toLower(movie.title).find(lowerQuery) != std::string::npos)
                    results.push_back(movie);
                break;
            case 2:
                if (toLower(movie.language).find(query) != std::string::npos)
                    results.push_back(movie);
                break;
            case 3:
                if (toLower(movie.genre).find(query) != std::string::npos)
                    results.push_back(movie);
                break;
            case 4:
                if (toLower(movie.releaseDate).find(query) != std::string::npos)
                    results.push_back(movie);
                break;
            default:
                std::cout << "Invalid choice.\n";
                return;
        }
    }

    if (results.empty()) {
        std::cout << "No matching movies found.\n";
    } else {
        std::cout << "\nSearch Results:\n";
        std::cout << "----------------------------------------\n";
        for (const auto& movie : results) {
            displayMovie(movie);
        }
    }


    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
}
