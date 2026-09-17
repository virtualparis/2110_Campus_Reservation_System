#include "../include/WaitingList.h"
#include <iostream>
#include <queue>

void WaitingList::addStudent(const WaitingRequest& request) {
    requests.push(request);
}

bool WaitingList::removeNextStudent(WaitingRequest& request) {
    if (requests.empty()) {
        return false;
    }

    request = requests.front();
    requests.pop();
    return true;
}

void WaitingList::displayWaitingList() const {
    if (requests.empty()) {
        std::cout << "Waiting list is empty." << std::endl;
        return;
    }

    std::queue<WaitingRequest> copy = requests;

    while (!copy.empty()) {
        WaitingRequest request = copy.front();

        std::cout << "Student ID: " << request.studentId
                  << ", Name: " << request.studentName
                  << ", Resource ID: " << request.resourceId
                  << std::endl;

        copy.pop();
    }
}

bool WaitingList::isEmpty() const {
    return requests.empty();
}
