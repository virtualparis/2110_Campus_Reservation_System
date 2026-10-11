#include "Reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation()
{
    reservationID = 0;
    studentID = 0;
    resourceID = 0;
    studentName = "";
    resourceName = "";
    reservationDate = "";
}

Reservation::Reservation(int reservationID, int studentID, int resourceID,
                         string studentName, string resourceName,
                         string reservationDate)
{
    this->reservationID = reservationID;
    this->studentID = studentID;
    this->resourceID = resourceID;
    this->studentName = studentName;
    this->resourceName = resourceName;
    this->reservationDate = reservationDate;
}

int Reservation::getReservationID() const
{
    return reservationID;
}

int Reservation::getStudentID() const
{
    return studentID;
}

int Reservation::getResourceID() const
{
    return resourceID;
}

string Reservation::getStudentName() const
{
    return studentName;
}

string Reservation::getResourceName() const
{
    return resourceName;
}

string Reservation::getReservationDate() const
{
    return reservationDate;
}

void Reservation::display() const
{
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "Resource Name: " << resourceName << endl;
    cout << "Reservation Date: " << reservationDate << endl;
}
