#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <list>
#include <string>

#include "CancellationHistory.h"
#include "Reservation.h"
#include "Resources.h"
#include "WaitingList.h"

class ReservationManager {
private:
    std::list<Reservation> activeReservations;
    CancellationHistory cancellationHistory;
    WaitingList waitingList;
    int nextReservationID = 1;

    void assignNextStudentForResource(
        const std::string& resourceID);

public:
    void loadResources(const std::string& filename);
    void loadReservations(const std::string& filename);

    void createReservation(int reservationID, int studentID,
                           const std::string& resourceID,
                           const std::string& studentName,
                           const std::string& reservationDate);

    void cancelReservation(int reservationID);
    void undoCancellation();

    Reservation* findReservationByID(int reservationID);

    void displayResources() const;
    void displayActiveReservations() const;
    void displayCancellationHistory() const;
    void displayWaitingList() const;

    void sortResourcesByName();
    void sortResourcesByType();
    void sortResourcesByStatus();
};

#endif