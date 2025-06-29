#include <iostream>
#include "search_movies.h"
#include "menu.h"
#include "login.h"

void showWelcomeMenu() {
    std::cout << "+---------------------------------------+\n";
    std::cout << "|     Movie Ticket Booking System       |\n";
    std::cout << "+---------------------------------------+\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::string loggedInUserEmail;
    bool isAdmin = false;
    int choice;

    do {
        system("cls");
        showWelcomeMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (login(loggedInUserEmail, isAdmin)) {
                handleMenuChoice(isAdmin, loggedInUserEmail);
            }
            break;
        case 2:
            registerUser();
            break;
        case 3:
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            system("pause");
        }
    } while (choice != 3);

    return 0;
}
