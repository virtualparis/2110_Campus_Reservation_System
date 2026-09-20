#include "ReservationManager.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

bool isNumber(const std::string& text) {
    if (text.empty()) {
        return false;
    }

    for (char character : text) {
        if (!std::isdigit(
                static_cast<unsigned char>(character))) {
            return false;
        }
    }

    return true;
}

void ReservationManager::loadResources(
    const std::string& filename) {

    Resource::loadResources(filename);
}

void ReservationManager::loadReservations(
    const std::string& filename) {

    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening reservation file: "
                  << filename << '\n';
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string reservationID;
        std::string studentID;
        std::string studentName;
        std::string resourceID;
        std::string reservationDate;

        std::getline(ss, reservationID, '|');
        std::getline(ss, studentID, '|');
        std::getline(ss, studentName, '|');
        std::getline(ss, resourceID, '|');
        std::getline(ss, reservationDate, '|');

        if (!isNumber(reservationID) ||
            !isNumber(studentID) || resourceID.empty()) {
            std::cerr << "Invalid reservation data: "
                      << line << '\n';
            continue;
        }

        Resource* resource = Resource::searchByID(resourceID);
        std::string resourceName = "Unknown Resource";

        if (resource != nullptr) {
            resourceName = resource->getresourceName();
        }

        int id = std::stoi(reservationID);
        int student = std::stoi(studentID);

        activeReservations.emplace_back(
            id, student, resourceID, studentName,
            resourceName, reservationDate);

        if (id >= nextReservationID) {
            nextReservationID = id + 1;
        }
    }
}

void ReservationManager::createReservation(
    int reservationID, int studentID,
    const std::string& resourceID,
    const std::string& studentName,
    const std::string& reservationDate) {

    if (findReservationByID(reservationID) != nullptr) {
        std::cout << "Reservation ID already exists.\n";
        return;
    }

    Resource* resource = Resource::searchByID(resourceID);

    if (resource == nullptr) {
        std::cout << "Resource not found.\n";
        return;
    }

    if (resource->getavailabilityStatus() != "Available") {
        WaitingRequest request;
        request.studentId = studentID;
        request.studentName = studentName;
        request.resourceId = resourceID;

        waitingList.addStudent(request);

        std::cout << "Resource is unavailable. Student added "
                  << "to the waiting list.\n";
        return;
    }

    activeReservations.emplace_back(
        reservationID, studentID, resourceID, studentName,
        resource->getresourceName(), reservationDate);

    resource->setAvailabilityStatus("Unavailable");

    if (reservationID >= nextReservationID) {
        nextReservationID = reservationID + 1;
    }

    std::cout << "Reservation created successfully.\n";
}

void ReservationManager::cancelReservation(int reservationID) {
    for (auto it = activeReservations.begin();
         it != activeReservations.end(); ++it) {

        if (it->getReservationID() == reservationID) {
            Reservation cancelled = *it;

            cancellationHistory.addCancelledReservation(
                cancelled);

            activeReservations.erase(it);

            Resource* resource = Resource::searchByID(
                cancelled.getResourceID());

            if (resource != nullptr) {
                resource->setAvailabilityStatus("Available");
            }

            std::cout << "Reservation cancelled successfully.\n";

            assignNextStudentForResource(
                cancelled.getResourceID());

            return;
        }
    }

    std::cout << "Reservation not found.\n";
}

void ReservationManager::assignNextStudentForResource(
    const std::string& resourceID) {

    WaitingRequest nextStudent;

    if (!waitingList.removeNextStudentForResource(
            resourceID, nextStudent)) {
        return;
    }

    std::cout << "Assigning resource " << resourceID
              << " to the next waiting student: "
              << nextStudent.studentName << '\n';

    createReservation(
        nextReservationID,
        nextStudent.studentId,
        nextStudent.resourceId,
        nextStudent.studentName,
        "Assigned after cancellation");
}

void ReservationManager::undoCancellation() {
    Reservation restored;

    if (!cancellationHistory.undoCancellation(restored)) {
        std::cout << "No cancellations to undo.\n";
        return;
    }

    Resource* resource = Resource::searchByID(
        restored.getResourceID());

    if (resource == nullptr ||
        resource->getavailabilityStatus() != "Available") {

        cancellationHistory.addCancelledReservation(restored);

        std::cout << "Cannot restore reservation because "
                  << "the resource is unavailable.\n";
        return;
    }

    activeReservations.push_back(restored);
    resource->setAvailabilityStatus("Unavailable");

    std::cout << "Most recent cancellation restored.\n";
}

Reservation* ReservationManager::findReservationByID(
    int reservationID) {

    for (auto& reservation : activeReservations) {
        if (reservation.getReservationID() == reservationID) {
            return &reservation;
        }
    }

    return nullptr;
}

void ReservationManager::displayResources() const {
    Resource::displayAll();
}

void ReservationManager::displayActiveReservations() const {
    if (activeReservations.empty()) {
        std::cout << "No active reservations.\n";
        return;
    }

    for (const auto& reservation : activeReservations) {
        reservation.display();
        std::cout << "-------------------------\n";
    }
}

void ReservationManager::displayWaitingList() const {
    waitingList.displayWaitingList();
}

void ReservationManager::displayCancellationHistory() const {
    cancellationHistory.displayCancellationHistory();
}

void ReservationManager::sortResourcesByName() {
    Resource::sortByName();
}

void ReservationManager::sortResourcesByType() {
    Resource::sortByType();
}

void ReservationManager::sortResourcesByStatus() {
    Resource::sortByStatus();
}