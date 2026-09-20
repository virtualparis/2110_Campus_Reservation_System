#include "CancellationManager.h"
#include <iostream>

using namespace std;

CancellationManager::CancellationManager()
{
    nextReservationID = 1;
}

bool CancellationManager::createReservation(
    int studentID,
    int resourceID,
    string studentName,
    string resourceName,
    string reservationDate)
{
    if (activeReservations.hasResource(resourceID))
    {
        cout << "Resource is already reserved." << endl;
        return false;
    }

    if (activeReservations.hasStudentReservation(
            studentID, resourceID))
    {
        cout << "Student already has this reservation." << endl;
        return false;
    }

    Reservation newReservation(
        nextReservationID,
        studentID,
        resourceID,
        studentName,
        resourceName,
        reservationDate
    );

    if (activeReservations.insertReservation(newReservation))
    {
        cout << "Reservation created successfully." << endl;
        cout << "Reservation ID: "
             << nextReservationID << endl;

        nextReservationID++;

        return true;
    }

    return false;
}

bool CancellationManager::cancelReservation(
    int reservationID,
    Reservation& cancelledReservation)
{
    if (!activeReservations.removeReservation(
            reservationID, cancelledReservation))
    {
        cout << "Reservation not found." << endl;
        return false;
    }

    cout << "Reservation cancelled successfully." << endl;

    return true;
}

bool CancellationManager::canRestoreReservation(
    const Reservation& reservation) const
{
    if (activeReservations.hasResource(
            reservation.getResourceID()))
    {
        return false;
    }

    if (activeReservations.hasStudentReservation(
            reservation.getStudentID(),
            reservation.getResourceID()))
    {
        return false;
    }

    return true;
}

bool CancellationManager::restoreReservation(
    const Reservation& reservation)
{
    if (!canRestoreReservation(reservation))
    {
        cout << "Cannot restore reservation." << endl;
        cout << "The resource is already assigned to "
             << "another reservation." << endl;

        return false;
    }
    
    if (activeReservations.insertReservation(reservation))
    {
        cout << "Reservation restored successfully."
             << endl;

        return true;
    }

    cout << "Reservation could not be restored." << endl;

    return false;
}

void CancellationManager::displayActiveReservations() const
{
    activeReservations.displayReservations();
}

bool CancellationManager::reservationExists(
    int reservationID) const
{
    Reservation foundReservation;

    return activeReservations.findReservation(
        reservationID,
        foundReservation);
}

bool CancellationManager::resourceReserved(
    int resourceID) const
{
    return activeReservations.hasResource(resourceID);
}
