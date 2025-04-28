#include <iostream>
#include <string>
#include <iomanip> // For setw

void displayMenu() {
    std::cout << "\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |       Movie Ticket        |\n";
    std::cout << "  |         System            |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  | 1. Search Movies          |\n";
    std::cout << "  | 2. Book Ticket            |\n";
    std::cout << "  | 3. View Bookings          |\n";
    std::cout << "  | 4. Access Admin Panel     |\n";
    std::cout << "  | 5. Exit                   |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  Enter your choice: ";
}

void searchMovies() {
    std::string city;
    std::cout << "\nPlease choose a city (Sofia, Plovdiv, Varna, Burgas, Ruse): ";
    std::cin >> city;
    std::cout << "Searching movies in " << city << "..." << std::endl;
}

void handleMenuChoice() {
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            searchMovies();
            break;
        case 2:
            std::cout << "\nBooking Ticket..." << std::endl;
            // Add booking functionality here
            break;
        case 3:
            std::cout << "\nViewing Bookings..." << std::endl;
            // Add view bookings functionality here
            break;
        case 4:
            std::cout << "\nAccessing Admin Panel..." << std::endl;
            // Add admin panel functionality here
            break;
        case 5:
            std::cout << "\nExiting the system. Thank you!\n" << std::endl;
            break;
        default:
            std::cout << "\nInvalid choice. Please try again.\n" << std::endl;
        }
    } while (choice != 5);
}