#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
private:
    int reservationID;
    int studentID;
    int resourceID;
    string studentName;
    string resourceName;
    string reservationDate;

public:
    Reservation();

    Reservation(int reservationID, int studentID, int resourceID,
                string studentName, string resourceName,
                string reservationDate);

    int getReservationID() const;
    int getStudentID() const;
    int getResourceID() const;

    string getStudentName() const;
    string getResourceName() const;
    string getReservationDate() const;

    void display() const;
};

#endif
