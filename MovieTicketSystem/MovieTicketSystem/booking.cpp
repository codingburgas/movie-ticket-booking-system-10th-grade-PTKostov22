#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

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

std::vector<std::string> loadBookedSeats(const std::string& movie, const std::string& cinema, const std::string& time) {
    std::vector<std::string> bookedSeats;
    std::ifstream in("booked_seats.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string m, c, t, seat;
        std::getline(ss, m, '|');
        std::getline(ss, c, '|');
        std::getline(ss, t, '|');

        if (m == movie && c == cinema && t == time) {
            while (std::getline(ss, seat, ',')) {
                bookedSeats.push_back(seat);
            }
        }
    }
    return bookedSeats;
}

std::vector<std::vector<Seat>> generateSeatLayout(const std::vector<std::string>& bookedSeats) {
    std::vector<std::vector<Seat>> layout;
    for (char row = 'A'; row <= 'J'; ++row) {
        std::vector<Seat> seatRow;
        for (int col = 1; col <= 15; ++col) {
            Seat seat;
            seat.id = row + std::to_string(col);
            seat.status = std::find(bookedSeats.begin(), bookedSeats.end(), seat.id) != bookedSeats.end()
                ? BOOKED : AVAILABLE;
            seatRow.push_back(seat);
        }
        layout.push_back(seatRow);
    }
    return layout;
}

void displaySeatLayout(const std::vector<std::vector<Seat>>& layout) {
    std::cout << "\nSeat Layout (Green = Available, Red = Booked):\n\n";
    for (const auto& row : layout) {
        for (const auto& seat : row) {
            switch (seat.status) {
            case AVAILABLE:
                std::cout << "\033[32m" << seat.id << "\033[0m ";
                break;
            case BOOKED:
                std::cout << "\033[31m" << seat.id << "\033[0m ";
                break;
            default:
                std::cout << seat.id << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nSeat Layout (Green = Available, Red = Booked):\n\n";
    for (const auto& row : layout) {
        for (const auto& seat : row) {
            switch (seat.status) {
            case AVAILABLE:
                std::cout << "\033[32m" << seat.id << "\033[0m ";
                break;
            case BOOKED:
                std::cout << "\033[31m" << seat.id << "\033[0m ";
                break;
            default:
                std::cout << seat.id << " ";
            }
        }
        std::cout << "\n";
    }
}

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

void selectSeats(const std::string& loggedInUserEmail) {
    clearScreen();
    std::cout << "DEBUG: Received loggedInUserEmail = '" << loggedInUserEmail << "'\n";

    std::vector<std::string> cities = { "Sofia", "Plovdiv", "Varna", "Burgas", "Ruse" };
    std::map<std::string, std::vector<std::string>> cinemas = {
        {"Sofia", {"Mall of Sofia", "Paradise Center", "Arena Mladost"}},
        {"Plovdiv", {"Markovo Tepe", "Mall Plovdiv"}},
        {"Varna", {"Grand Mall", "Varna Towers"}},
        {"Burgas", {"Galleria Burgas", "Mall Burgas Plaza"}},
        {"Ruse", {"Mall Ruse", "Royal City Cinema"}}
    };

    std::vector<MovieSchedule> schedule = loadSchedule();

    std::cout << "Select a City:\n";
    for (size_t i = 0; i < cities.size(); ++i)
        std::cout << i + 1 << ". " << cities[i] << "\n";
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
    for (size_t i = 0; i < cinemaList.size(); ++i)
        std::cout << i + 1 << ". " << cinemaList[i] << "\n";
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
    std::cout << "Available Movies:\n";
    for (size_t i = 0; i < schedule.size(); ++i)
        std::cout << i + 1 << ". " << schedule[i].title << "\n";
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

    clearScreen();
    std::cout << "Available Showtimes for " << selectedMovie.title << ":\n";
    for (size_t i = 0; i < selectedMovie.showtimes.size(); ++i)
        std::cout << i + 1 << ". " << selectedMovie.showtimes[i] << "\n";
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

    std::vector<std::string> bookedSeats = loadBookedSeats(selectedMovie.title, selectedCinema, selectedTime);
    auto layout = generateSeatLayout(bookedSeats);
    displaySeatLayout(layout);

    int numberOfSeats;
    std::cout << "\nEnter number of seats to book: ";
    std::cin >> numberOfSeats;
    std::cin.ignore();

    std::vector<std::string> selectedSeats;
    for (int i = 0; i < numberOfSeats; ++i) {
        std::string seatId;
        std::cout << "Enter Seat ID (e.g., A1): ";
        std::getline(std::cin, seatId);
        selectedSeats.push_back(seatId);
    }

    std::cout << "\nConfirm booking? (Y/N): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'Y' || confirm == 'y') {
        std::string username = "unknown_user";
        size_t atPos = loggedInUserEmail.find('@');
        if (atPos != std::string::npos) {
            username = loggedInUserEmail.substr(0, atPos);
        }

        std::cout << "DEBUG: Extracted username = '" << username << "'\n";

        std::string profilePath = "profiles/" + username + ".txt";
        std::ofstream profile(profilePath, std::ios::app);

        if (profile.is_open()) {
            profile << "\nBooking:\n";
            profile << "Movie: " << selectedMovie.title << "\n";
            profile << "City: " << selectedCity << "\n";
            profile << "Cinema: " << selectedCinema << "\n";
            profile << "Showtime: " << selectedTime << "\n";
            profile << "Seats: ";
            for (const std::string& seat : selectedSeats)
                profile << seat << " ";
            profile << "\n";
            profile.close();

            std::cout << "\nBooking confirmed and saved to your profile!\n";
        }
        else {
            std::cout << "\nERROR: Could not open user profile file.\n";
        }

        std::ofstream bookedFile("booked_seats.txt", std::ios::app);
        if (bookedFile.is_open()) {
            bookedFile << selectedMovie.title << "|" << selectedCinema << "|" << selectedTime;
            for (const auto& seat : selectedSeats) {
                bookedFile << "|" << seat;
            }
            bookedFile << "\n";
            bookedFile.close();
        }
    }
    else {
        std::cout << "Booking canceled.\n";
    }

    pauseScreen();
}

