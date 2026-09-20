#include "Reservation.h"
#include <iostream>

Reservation::Reservation()
    : reservationID(0), studentID(0), resourceID(""),
      studentName(""), resourceName(""), reservationDate("") {
}

Reservation::Reservation(int reservationID, int studentID,
                         const std::string& resourceID,
                         const std::string& studentName,
                         const std::string& resourceName,
                         const std::string& reservationDate)
    : reservationID(reservationID), studentID(studentID),
      resourceID(resourceID), studentName(studentName),
      resourceName(resourceName), reservationDate(reservationDate) {
}

int Reservation::getReservationID() const {
    return reservationID;
}

int Reservation::getStudentID() const {
    return studentID;
}

std::string Reservation::getResourceID() const {
    return resourceID;
}

std::string Reservation::getStudentName() const {
    return studentName;
}

std::string Reservation::getResourceName() const {
    return resourceName;
}

std::string Reservation::getReservationDate() const {
    return reservationDate;
}

void Reservation::display() const {
    std::cout << "Reservation ID: " << reservationID << '\n';
    std::cout << "Student ID: " << studentID << '\n';
    std::cout << "Student Name: " << studentName << '\n';
    std::cout << "Resource ID: " << resourceID << '\n';
    std::cout << "Resource Name: " << resourceName << '\n';
    std::cout << "Reservation Date: " << reservationDate << '\n';
}