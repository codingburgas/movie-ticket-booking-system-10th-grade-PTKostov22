#include <iostream>
#include <string>
#include <iomanip>
#include "menu.h"

void displayMenu(bool isAdmin) {
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "          Movie Ticket Booking System     \n";
    std::cout << "=========================================\n";
    std::cout << "1. Search Movies\n";
    std::cout << "2. Book Ticket\n";
    std::cout << "3. View Bookings\n";
    if (isAdmin) {
        std::cout << "4. Admin Panel\n";
        std::cout << "5. Exit\n";
    }
    else {
        std::cout << "4. Exit\n";
    }
    std::cout << "=========================================\n";
    std::cout << "Enter your choice: ";
}

void handleMenuChoice(bool isAdmin) {
    int choice;

    do {
        displayMenu(isAdmin);
        std::cin >> choice;

        if (isAdmin) {
            switch (choice) {
            case 1:
                searchMovies();
                break;
            case 2:
                std::cout << "\nBooking Ticket...\n\n";
                system("pause");
                break;
            case 3:
                std::cout << "\nViewing Bookings...\n\n";
                system("pause");
                break;
            case 4:
                std::cout << "\nAccessing Admin Panel...\n\n";
                system("pause");
                break;
            case 5:
                std::cout << "\nЕxiting the system. Thank you!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n\n";
                system("pause");
            }
        }
        else {
            switch (choice) {
            case 1:
                searchMovies();
                break;
            case 2:
                std::cout << "\nBooking Ticket...\n\n";
                system("pause");
                break;
            case 3:
                std::cout << "\nViewing Bookings...\n\n";
                system("pause");
                break;
            case 4:
                std::cout << "\nExiting the system. Thank you!\n";
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n\n";
                system("pause");
            }
        }
    } while ((isAdmin && choice != 5) || (!isAdmin && choice != 4));
}

void searchMovies() {
    std::string city;
    std::cout << "\nPlease choose a city (Sofia, Plovdiv, Varna, Burgas, Ruse): ";
    std::cin >> city;
    std::cout << "\n🔎 Searching movies in " << city << "...\n\n";
    system("pause");
}
