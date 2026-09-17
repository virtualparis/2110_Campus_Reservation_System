/* Main function */

#include <iostream>
#include "ReservationManager.h"
using namespace std;

int main() {
    ReservationManager manager;

    // load reservations and resources from a file
    manager.loadReservations("reservations.txt");
    manager.loadResources("resources.txt");

    // menu with prompts for user
    int choice;
    do {
        cout << "==== Campus Resource Reservation System ====\n";
        cout << "1. View Resources\n";
        cout << "2. Create Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. View Waiting Lists\n";
        cout << "5. Undo Cancellation\n";
        cout << "6. Search Reservations\n";
        cout << "7. Sort Resources\n";
        cout << "8. Generate Report\n";
        cout << "9. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
    }


    return 0;
}