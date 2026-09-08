#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include "Reservation.h"

class CancellationHistory {
private:
    std::stack<Reservation> cancelledReservations;

public:
    void addCancelledReservation(const Reservation& reservation);
    bool undoCancellation(Reservation& reservation);
    void displayCancellationHistory() const;
    bool isEmpty() const;
};

#endif
