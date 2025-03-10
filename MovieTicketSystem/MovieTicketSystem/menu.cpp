#include <iostream>
#include <string>
#include "menu.h"

void displayMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. Search Movies\n";
    std::cout << "2. Book Ticket\n";
    std::cout << "3. View Bookings\n";
    std::cout << "4. Access Admin Panel\n";
    std::cout << "5. Exit\n";
}

void searchMovies() {
    std::string city;
    std::cout << "Please choose a city (Sofia, Plovdiv, Varna, Burgas, Ruse): ";
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
            std::cout << "Booking Ticket..." << std::endl;
            // Add booking functionality here
            break;
        case 3:
            std::cout << "Viewing Bookings..." << std::endl;
            // Add view bookings functionality here
            break;
        case 4:
            std::cout << "Accessing Admin Panel..." << std::endl;
            // Add admin panel functionality here
            break;
        case 5:
            std::cout << "Exiting the system. Thank you!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);
}