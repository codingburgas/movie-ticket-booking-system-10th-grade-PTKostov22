#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

enum SeatStatus { AVAILABLE, RESERVED, BOOKED };

struct Seat {
    std::string id;
    SeatStatus status;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void displaySeatLayout(const std::vector<std::vector<Seat>>& layout) {
    std::cout << "\nSeat Layout (Green = Available, Gray = Reserved, Red = Booked):\n\n";
    for (const auto& row : layout) {
        for (const auto& seat : row) {
            switch (seat.status) {
                case AVAILABLE:
                    std::cout << "\033[32m" << seat.id << "\033[0m ";
                    break;
                case RESERVED:
                    std::cout << "\033[37m" << seat.id << "\033[0m ";
                    break;
                case BOOKED:
                    std::cout << "\033[31m" << seat.id << "\033[0m ";
                    break;
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<Seat>> generateSeatLayout() {
    std::vector<std::vector<Seat>> layout;
    for (char row = 'A'; row <= 'J'; ++row) {
        std::vector<Seat> seatRow;
        for (int col = 1; col <= 15; ++col) {
            Seat seat;
            seat.id = row + std::to_string(col);
            seat.status = AVAILABLE;
            seatRow.push_back(seat);
        }
        layout.push_back(seatRow);
    }
    return layout;
}

void selectSeats() {
    clearScreen();

    std::vector<std::string> cities = {"Sofia", "Plovdiv", "Varna", "Burgas", "Ruse"};
    std::map<std::string, std::vector<std::string>> cinemas = {
        {"Sofia", {"Mall of Sofia", "Paradise Center", "Arena Mladost"}},
        {"Plovdiv", {"Markovo Tepe", "Mall Plovdiv"}},
        {"Varna", {"Grand Mall", "Varna Towers"}},
        {"Burgas", {"Galleria Burgas", "Mall Burgas Plaza"}},
        {"Ruse", {"Mall Ruse", "Royal City Cinema"}}
    };
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> movies = {
        {"Mall of Sofia", {{"Avatar", "14:00"}, {"Titanic", "17:00"}}},
        {"Paradise Center", {{"Amelie", "15:30"}, {"Parasite", "18:00"}}},
        {"Arena Mladost", {{"The Matrix", "20:00"}}},
        {"Markovo Tepe", {{"Inception", "16:00"}}},
        {"Mall Plovdiv", {{"Interstellar", "19:00"}}},
        {"Grand Mall", {{"Joker", "13:00"}}},
        {"Varna Towers", {{"Frozen", "11:00"}}},
        {"Galleria Burgas", {{"Up", "10:00"}}},
        {"Mall Burgas Plaza", {{"Soul", "12:00"}}},
        {"Mall Ruse", {{"Coco", "14:30"}}},
        {"Royal City Cinema", {{"Inside Out", "16:30"}}}
    };

    std::cout << "Select a City:\n";
    for (size_t i = 0; i < cities.size(); ++i) {
        std::cout << i + 1 << ". " << cities[i] << "\n";
    }
    std::cout << "Enter choice: ";
    int cityChoice;
    std::cin >> cityChoice;
    std::cin.ignore();
    if (cityChoice < 1 || cityChoice > cities.size()) {
        std::cout << "Invalid city selection.\n";
        pauseScreen();
        return;
    }
    std::string selectedCity = cities[cityChoice - 1];

    clearScreen();
    std::cout << "Select a Cinema in " << selectedCity << ":\n";
    const auto& cinemaList = cinemas[selectedCity];
    for (size_t i = 0; i < cinemaList.size(); ++i) {
        std::cout << i + 1 << ". " << cinemaList[i] << "\n";
    }
    std::cout << "Enter choice: ";
    int cinemaChoice;
    std::cin >> cinemaChoice;
    std::cin.ignore();
    if (cinemaChoice < 1 || cinemaChoice > cinemaList.size()) {
        std::cout << "Invalid cinema selection.\n";
        pauseScreen();
        return;
    }
    std::string selectedCinema = cinemaList[cinemaChoice - 1];

    clearScreen();
    std::cout << "Available Movies at " << selectedCinema << ":\n";
    const auto& movieList = movies[selectedCinema];
    for (size_t i = 0; i < movieList.size(); ++i) {
        std::cout << i + 1 << ". " << movieList[i].first << " at " << movieList[i].second << "\n";
    }
    std::cout << "Enter choice: ";
    int movieChoice;
    std::cin >> movieChoice;
    std::cin.ignore();
    if (movieChoice < 1 || movieChoice > movieList.size()) {
        std::cout << "Invalid movie selection.\n";
        pauseScreen();
        return;
    }
    std::string selectedMovie = movieList[movieChoice - 1].first;
    std::string selectedTime = movieList[movieChoice - 1].second;

    clearScreen();
    std::cout << "Booking Summary:\n";
    std::cout << "City: " << selectedCity << "\n";
    std::cout << "Cinema: " << selectedCinema << "\n";
    std::cout << "Movie: " << selectedMovie << "\n";
    std::cout << "Showtime: " << selectedTime << "\n";

    auto layout = generateSeatLayout();
    displaySeatLayout(layout);

    pauseScreen();
}
