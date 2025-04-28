#include <iostream>
#include <string>
#include <iomanip>
#include "menu.h" // Include the header
#include "login.h"

void displayMenu() {
    // ... (Menu display code as in the latest version)
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
            std::cout << "\\nBooking Ticket...\\n" << std::endl;
            // Add booking functionality here
            break;
        case 3:
            std::cout << "\\nViewing Bookings...\\n" << std::endl;
            // Add view bookings functionality here
            break;
        case 4:
            std::cout << "\\nAccessing Admin Panel...\\n" << std::endl;
            // Add admin panel functionality here
            break;
        case 5:
            std::cout << "\\nExiting the system. Thank you!\\n" << std::endl;
            break;
        default:
            std::cout << "\\nInvalid choice. Please try again.\\n" << std::endl;
        }
    } while (choice != 5);
}

void searchMovies() {
    std::string city;
    std::cout << "\\nPlease choose a city (Sofia, Plovdiv, Varna, Burgas, Ruse): ";
    std::cin >> city;
    std::cout << "Searching movies in " << city << "...\\n" << std::endl;
}