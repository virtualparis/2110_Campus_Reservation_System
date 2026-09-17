// header file for ReservationManager class

// define the ReservationManager class if it has not been defined yet
#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <list>
#include <string>
// include code from other header files here pls dontforget paris
#include "Reservation.h"
#include "CancellationHistory.h"
#include "WaitingList.h"

// class definition for ReservationManager
class ReservationManager {

    private:
        std::list<Reservation> activeReservations; // linked list of active reservations
        CancellationHistory cancellationHistory; // stack of cancelled reservations
        WaitingList waitingList; // queue of students waiting for a reservation

    public:
        // loading the reservations from a file
        void loadReservations(const std::string& filename);

        // creating a reservation, cancelling a reservation, and undoing a cancellation
        void createReservation(int reservationID, int studentID, int resourceID,
                               const std::string& studentName,
                               const std::string& resourceName,
                               const std::string& reservationDate);
        void cancelReservation(int reservationID);
        void undoCancellation();

        // searching for a reservation by ID and displaying all active reservations
        Reservation* searchReservation(int reservationID);

        // displaying the active reservations, cancellation history, and waiting list
        void displayActiveReservations() const;
        void displayCancellationHistory() const;
        void displayWaitingList() const;

};

#endif
