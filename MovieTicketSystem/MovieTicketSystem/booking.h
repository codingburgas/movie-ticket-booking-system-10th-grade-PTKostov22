#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>

// Enum to represent seat status
enum class SeatStatus {
    AVAILABLE,
    RESERVED,
    BOOKED
};

// Struct to represent a seat
struct Seat {
    std::string id;
    std::string type; // silver, gold, platinum
    SeatStatus status;
};

// Function declaration
void selectSeats();

#endif // BOOKING_H
