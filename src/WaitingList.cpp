#include "../include/WaitingList.h"
#include <iostream>

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

bool WaitingList::removeNextStudentForResource(
    const std::string& resourceId,
    WaitingRequest& request) {

    std::queue<WaitingRequest> remainingRequests;
    bool found = false;

    while (!requests.empty()) {
        WaitingRequest current = requests.front();
        requests.pop();

        if (!found && current.resourceId == resourceId) {
            request = current;
            found = true;
        } else {
            remainingRequests.push(current);
        }
    }

    requests = remainingRequests;
    return found;
}

void WaitingList::displayWaitingList() const {
    if (requests.empty()) {
        std::cout << "Waiting list is empty.\n";
        return;
    }

    std::queue<WaitingRequest> copy = requests;

    while (!copy.empty()) {
        WaitingRequest request = copy.front();

        std::cout << "Student ID: " << request.studentId
                  << ", Name: " << request.studentName
                  << ", Resource ID: " << request.resourceId
                  << '\n';

        copy.pop();
    }
}

bool WaitingList::isEmpty() const {
    return requests.empty();
}
