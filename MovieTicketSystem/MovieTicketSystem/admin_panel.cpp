#include <iostream>
#include "admin_panel.h"

void adminPanel() {
    int choice = 0;
    do {
        system("cls");
        std::cout << "=== Admin Panel ===\n";
        std::cout << "1. Add a movie\n";
        std::cout << "2. Update a movie\n";
        std::cout << "3. Delete a movie\n";
        std::cout << "4. Add Admin\n";
        std::cout << "5. Return to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            addMovieToSchedule();
            break;
        case 2:
            updateMovie();
            break;
        case 3:
            deleteMovie();
            break;
        case 4:
            addAdmin();
            break;
        case 5:
            std::cout << "Returning to main menu...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
        if (choice != 5) {
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    } while (choice != 5);
}
