#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

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

struct MovieSchedule {
    std::string title;
    std::vector<std::string> showtimes;
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

// Load the predefined schedule for all cinemas
std::vector<MovieSchedule> loadSchedule() {
    std::vector<MovieSchedule> schedule;
    std::ifstream file("schedule.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, times;

        std::getline(ss, title, '|');
        std::getline(ss, times);

        MovieSchedule ms;
        ms.title = title;

        std::stringstream ts(times);
        std::string time;
        while (std::getline(ts, time, ',')) {
            ms.showtimes.push_back(time);
        }

        schedule.push_back(ms);
    }

    return schedule;
}

void selectSeats() {
    clearScreen();

    std::vector<std::string> cities = { "Sofia", "Plovdiv", "Varna", "Burgas", "Ruse" };
    std::map<std::string, std::vector<std::string>> cinemas = {
        {"Sofia", {"Mall of Sofia", "Paradise Center", "Arena Mladost"}},
        {"Plovdiv", {"Markovo Tepe", "Mall Plovdiv"}},
        {"Varna", {"Grand Mall", "Varna Towers"}},
        {"Burgas", {"Galleria Burgas", "Mall Burgas Plaza"}},
        {"Ruse", {"Mall Ruse", "Royal City Cinema"}}
    };

    std::vector<MovieSchedule> schedule = loadSchedule();

    // Select city
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
    const auto& cinemaList = cinemas[selectedCity];
    std::cout << "Select a Cinema in " << selectedCity << ":\n";
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

    // Select movie from the schedule
    clearScreen();
    std::cout << "Available Movies:\n";
    for (size_t i = 0; i < schedule.size(); ++i) {
        std::cout << i + 1 << ". " << schedule[i].title << "\n";
    }
    std::cout << "Enter choice: ";
    int movieChoice;
    std::cin >> movieChoice;
    std::cin.ignore();

    if (movieChoice < 1 || movieChoice > schedule.size()) {
        std::cout << "Invalid movie selection.\n";
        pauseScreen();
        return;
    }

    const MovieSchedule& selectedMovie = schedule[movieChoice - 1];

    // Select time
    clearScreen();
    std::cout << "Available Showtimes for " << selectedMovie.title << ":\n";
    for (size_t i = 0; i < selectedMovie.showtimes.size(); ++i) {
        std::cout << i + 1 << ". " << selectedMovie.showtimes[i] << "\n";
    }
    std::cout << "Enter choice: ";
    int timeChoice;
    std::cin >> timeChoice;
    std::cin.ignore();

    if (timeChoice < 1 || timeChoice > selectedMovie.showtimes.size()) {
        std::cout << "Invalid showtime selection.\n";
        pauseScreen();
        return;
    }
    std::string selectedTime = selectedMovie.showtimes[timeChoice - 1];

    clearScreen();
    std::cout << "Booking Summary:\n";
    std::cout << "City: " << selectedCity << "\n";
    std::cout << "Cinema: " << selectedCinema << "\n";
    std::cout << "Movie: " << selectedMovie.title << "\n";
    std::cout << "Showtime: " << selectedTime << "\n";

    auto layout = generateSeatLayout();
    displaySeatLayout(layout);

    pauseScreen();
}
