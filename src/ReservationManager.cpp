/*
Reservation manager to handle reservation operations such as
creating a reservation, cancelling a reservation, 
view current reservations, and search for reservations.
*/ 

#include "ReservationManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

// validate if a string is a number
bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// converting string to int
int strToInt(const string& s) {
    stringstream ss(s);
    int value = 0;
    ss >> value;
    return value;
}

// load reservations from a file and add them to the active reservations list
void ReservationManager::loadReservations(const string& filename) {
    ifstream file(filename);
    string line;

    // check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // if file is open, read each line for reservation information
    while (getline(file, line)) {

        stringstream ss(line);
        string reservationID, studentID, studentName, resourceID, reservationDate;

        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, reservationDate, '|');

        // validating int to string conversion for reservationID, studentID, and resourceID
        if (!isNumber(reservationID) || !isNumber(studentID) || !isNumber(resourceID)) {
            cerr << "Invalid data: " << line << endl;
            continue; // skip this line and continue with the next
        }

        // converting string to int for reservationID, studentID, and resourceID
        int reservationID = strToInt(reservationID);
        int studentID = strToInt(studentID);
        int resourceID = strToInt(resourceID);

        string resourceName = "";

        // reservation object to create a new reservation and add it to the active reservations list
        Reservation reservation(reservationID, studentID, resourceID, studentName, resourceName, reservationDate);
        activeReservations.push_back(reservation);
    }
}

// create a new reservation and add it to the active reservations list
void ReservationManager::createReservation(int reservationID, int studentID,
                                           int resourceID,
                                           const string& studentName,
                                           const string& resourceName,
                                           const string& date) {

    Reservation reservation(reservationID, studentID, resourceID,
                  studentName, resourceName, date);

    activeReservations.push_back(reservation);
}

// cancel reservation by reservation ID, add it to the cancellation history stack, and add the student to the waiting list
void ReservationManager::cancelReservation(int reservationID) {
    for (auto it = activeReservations.begin(); it != activeReservations.end(); ++it) {
        if (it->getReservationID() == reservationID) {

            cancelHistory.addCancelledReservation(*it);

            WaitingRequest req;
            req.studentId = it->getStudentID();
            req.studentName = it->getStudentName();
            req.resourceId = it->getResourceID();

            waitingList.addStudent(req);

            activeReservations.erase(it);
            return;
        }
    }

    cout << "Reservation not found.\n";
}

// undo the last cancellation by popping from the cancellation history stack and adding it back to the active reservations list
void ReservationManager::undoCancellation() {
    if (cancelHistory.isEmpty()) {
        cout << "No cancellations to undo.\n";
        return;
    }

    Reservation restored;
    if (cancelHistory.undoCancellation(restored)) {
        activeReservations.push_back(restored);
    }
}

Reservation* ReservationManager::findReservationByID(int reservationID) {
    for (auto& reservation : activeReservations) {
        if (reservation.getReservationID() == reservationID)
            return &reservation;
    }
    return nullptr;
}

// display all active reservations, waiting list, and cancellation history
void ReservationManager::displayAllReservations() const {
    for (const auto& reservation : activeReservations) {
        reservation.display();
        cout << "-------------------------\n";
    }
}

void ReservationManager::displayWaitingList() const {
    waitingList.displayWaitingList();
}

void ReservationManager::displayCancellationHistory() const {
    cancelHistory.displayCancellationHistory();
}
