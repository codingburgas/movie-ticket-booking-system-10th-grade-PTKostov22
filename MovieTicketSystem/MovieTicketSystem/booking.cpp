#include <iostream>
#include <vector>
#include <string>

enum SeatStatus {
    AVAILABLE,
    RESERVED,
    BOOKED
};

struct Seat {
    std::string id;
    SeatStatus status;
};

void printSeat(const Seat& seat) {
    std::string colorCode;
    switch (seat.status) {
        case AVAILABLE:
            colorCode = "\033[32m"; // Green
            break;
        case RESERVED:
            colorCode = "\033[90m"; // Gray
            break;
        case BOOKED:
            colorCode = "\033[31m"; // Red
            break;
    }
    std::cout << colorCode << seat.id << "\033[0m ";
}

void selectSeats() {
    const int rows = 10;
    const int cols = 15;
    std::vector<std::vector<Seat>> layout(rows, std::vector<Seat>(cols));

    // Initialize seat layout
    for (int i = 0; i < rows; ++i) {
        char rowChar = 'A' + i;
        for (int j = 0; j < cols; ++j) {
            layout[i][j].id = rowChar + std::to_string(j + 1);
            layout[i][j].status = AVAILABLE;
        }
    }

    layout[0][0].status = BOOKED;   // A1
    layout[1][1].status = RESERVED; // B2
    layout[2][2].status = BOOKED;   // C3

    // Display seat layout
    std::cout << "\nSeat Layout (Green = Available, Gray = Reserved, Red = Booked):\n\n";
    for (const auto& row : layout) {
        for (const auto& seat : row) {
            printSeat(seat);
        }
        std::cout << "\n";
    }
}
