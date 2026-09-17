#include "../include/CancellationHistory.h"
#include <iostream>

// Save a cancelled reservation on top of the stack.
void CancellationHistory::addCancelledReservation(
    const Reservation& reservation) {

    cancelledReservations.push(reservation);
}

// Return and remove the most recently cancelled reservation.
// The reservation manager must restore it to active reservations.
bool CancellationHistory::undoCancellation(
    Reservation& reservation) {

    if (cancelledReservations.empty()) {
        return false;
    }

    reservation = cancelledReservations.top();
    cancelledReservations.pop();
    return true;
}

// Display newest cancellations first without changing the stack.
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
