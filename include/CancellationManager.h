#ifndef CANCELLATIONMANAGER_H
#define CANCELLATIONMANAGER_H

#include "ReservationList.h"

class CancellationManager
{
private:
    ReservationList activeReservations;
    int nextReservationID;

public:
    CancellationManager();

    bool createReservation(int studentID,
                           string resourceID,
                           string studentName,
                           string resourceName,
                           string reservationDate);

    bool cancelReservation(int reservationID,
                           Reservation& cancelledReservation);

    bool canRestoreReservation(
        const Reservation& reservation) const;

    bool restoreReservation(
        const Reservation& reservation);

    void displayActiveReservations() const;

    bool reservationExists(int reservationID) const;

    bool resourceReserved(string resourceID) const;
};

#endif
