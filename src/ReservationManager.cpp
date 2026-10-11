#include "ReservationManager.h"
#include <map>
#include <iomanip>

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
    const std::string& reservationDate,
    bool countRequest) {

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
        if (countRequest) 
        {
            ++requestCounts[resourceID];
        }

        std::cout << "Resource is unavailable. Student added "
                  << "to the waiting list.\n";
        return;
    }

   activeReservations.emplace_back(
    reservationID, studentID, resourceID, studentName,
    resource->getresourceName(), reservationDate);

    resource->setAvailabilityStatus("Unavailable");

if (countRequest) {
    ++requestCounts[resourceID];
}

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
    const std::string& resourceID) 
    {

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
    "Assigned after cancellation",
    false);
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
void ReservationManager::displayMostRequestedResources() const {
    std::cout << "Reporting period: this program run.\n"
              << "Counts new accepted reservation and waiting-list "
              << "requests only.\n";

    if (requestCounts.empty()) {
        std::cout << "No new requests recorded yet.\n";
        return;
    }

    std::size_t highestCount = 0;
    std::size_t totalRequests = 0;

    for (const auto& entry : requestCounts) {
        totalRequests += entry.second;

        if (entry.second > highestCount) {
            highestCount = entry.second;
        }
    }

    std::cout << "Total accepted requests: "
              << totalRequests << '\n';

    std::cout << "\nRequests by resource:\n";

    for (const auto& entry : requestCounts) {
        std::cout << "Resource " << entry.first
                  << ": " << entry.second << " request(s)\n";
    }

    // Display every resource tied for the highest count.
    std::cout << "\nMost requested resource(s):\n";

    for (const auto& entry : requestCounts) {
        if (entry.second == highestCount) {
            std::cout << "Resource " << entry.first
                      << ": " << entry.second << " request(s)\n";
        }
    }
}

void ReservationManager::displayWaitingListStatistics() const {
    waitingList.displayStatistics();
}
void ReservationManager::displayResourceUtilization() const {
    std::map<std::string, int> reservationCounts;

    for (const auto& reservation : activeReservations) {
        reservationCounts[reservation.getResourceID()]++;
    }

    std::cout << std::left
              << std::setw(15) << "Resource ID"
              << std::setw(25) << "Resource Name"
              << "Reservations\n";

    std::cout << std::string(55, '-') << "\n";

    for (const auto& resource : Resource::resources) {
        std::string id = resource.getresourceID();

        std::cout << std::left
                  << std::setw(15) << id
                  << std::setw(25) << resource.getresourceName()
                  << reservationCounts[id] << "\n";
    }

    std::cout << "\nTotal Active Reservations: "
              << activeReservations.size() << "\n";
}