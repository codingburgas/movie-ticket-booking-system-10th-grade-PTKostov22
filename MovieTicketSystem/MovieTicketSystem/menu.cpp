#include <iostream>
#include <string>
#include <fstream>
#include "menu.h"
#include "search_movies.h"
#include "booking.h"
#include "view_booking.h"
#include "MovieTicketSystem.h"
#include "admin_panel.h"

void displayMenu(bool isAdmin) {
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "          Movie Ticket Booking System    \n";
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

void handleMenuChoice(bool isAdmin, const std::string& loggedInUserEmail) {
    int choice;

    do {
        displayMenu(isAdmin);
        std::cin >> choice;
        std::cin.ignore();

        if (isAdmin) {
            switch (choice) {
            case 1:
                searchMovies();
                break;
            case 2:
                selectSeats(loggedInUserEmail);
                break;
            case 3:
                viewBookings(loggedInUserEmail);
                break;
            case 4:
                adminPanel();
                break;
            case 5:
                std::cout << "\nExiting the system. Thank you!\n";
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
                selectSeats(loggedInUserEmail);
                break;
            case 3:
                viewBookings(loggedInUserEmail);
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

std::string getLoggedInUserEmail() {

    std::ifstream file("loggedInUser.txt");
    if (!file.is_open()) {
        return ""; 
    }
    std::string email;
    std::getline(file, email);
    file.close();
    return email;
}

void runMenu() {
    std::string email = getLoggedInUserEmail();
    bool adminFlag = isUserAdmin(email);
    handleMenuChoice(adminFlag, email);
}
