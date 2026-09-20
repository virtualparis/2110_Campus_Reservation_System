#include "../include/CancellationHistory.h"
#include <iostream>

void CancellationHistory::addCancelledReservation(
    const Reservation& reservation) {

    cancelledReservations.push(reservation);
}

bool CancellationHistory::undoCancellation(
    Reservation& reservation) {

    if (cancelledReservations.empty()) {
        return false;
    }

    reservation = cancelledReservations.top();
    cancelledReservations.pop();
    return true;
}

void CancellationHistory::displayCancellationHistory() const {
    if (cancelledReservations.empty()) {
        std::cout << "Cancellation history is empty.\n";
        return;
    }

    std::stack<Reservation> copy = cancelledReservations;

    while (!copy.empty()) {
        copy.top().display();
        std::cout << '\n';
        copy.pop();
    }
}

bool CancellationHistory::isEmpty() const {
    return cancelledReservations.empty();
}
