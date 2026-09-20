#include <iostream>
#include <limits>
#include <string>

#include "ReservationManager.h"

int readInt(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');
            return value;
        }

        std::cout << "Invalid input. Enter a number.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    ReservationManager manager;

    manager.loadResources("data/resources.txt");
    manager.loadReservations("data/reservations.txt");

    int choice;

    do {
        std::cout << "\n===== Campus Resource Reservation System =====\n";
        std::cout << "1. View Resources\n";
        std::cout << "2. Create Reservation\n";
        std::cout << "3. Cancel Reservation\n";
        std::cout << "4. View Waiting List\n";
        std::cout << "5. Undo Cancellation\n";
        std::cout << "6. Search Reservation\n";
        std::cout << "7. Sort and View Resources\n";
        std::cout << "8. Generate Report\n";
        std::cout << "9. Exit\n";

        choice = readInt("Enter choice: ");

        if (choice == 1) {
            manager.displayResources();
        }
        else if (choice == 2) {
            int reservationID =
                readInt("Reservation ID: ");
            int studentID =
                readInt("Student ID: ");

            std::string studentName;
            std::string resourceID;
            std::string date;

            std::cout << "Student name: ";
            std::getline(std::cin, studentName);

            std::cout << "Resource ID (example: R101): ";
            std::getline(std::cin, resourceID);

            std::cout << "Reservation date: ";
            std::getline(std::cin, date);

            manager.createReservation(
                reservationID, studentID, resourceID,
                studentName, date);
        }
        else if (choice == 3) {
            int reservationID =
                readInt("Reservation ID to cancel: ");

            manager.cancelReservation(reservationID);
        }
        else if (choice == 4) {
            manager.displayWaitingList();
        }
        else if (choice == 5) {
            manager.undoCancellation();
        }
        else if (choice == 6) {
            int reservationID =
                readInt("Reservation ID to search: ");

            Reservation* reservation =
                manager.findReservationByID(reservationID);

            if (reservation == nullptr) {
                std::cout << "Reservation not found.\n";
            } else {
                reservation->display();
            }
        }
        else if (choice == 7) {
            std::cout << "1. Sort by name\n";
            std::cout << "2. Sort by type\n";
            std::cout << "3. Sort by availability\n";

            int sortChoice = readInt("Enter sort choice: ");

            if (sortChoice == 1) {
                manager.sortResourcesByName();
            } else if (sortChoice == 2) {
                manager.sortResourcesByType();
            } else if (sortChoice == 3) {
                manager.sortResourcesByStatus();
            } else {
                std::cout << "Invalid sort choice.\n";
            }

            manager.displayResources();
        }
        else if (choice == 8) {
            std::cout << "\n--- Active Reservations ---\n";
            manager.displayActiveReservations();

            std::cout << "\n--- Waiting List ---\n";
            manager.displayWaitingList();

            std::cout << "\n--- Cancellation History ---\n";
            manager.displayCancellationHistory();
        }
        else if (choice != 9) {
            std::cout << "Invalid menu choice.\n";
        }

    } while (choice != 9);

    std::cout << "Goodbye.\n";
    return 0;
}