#include "../include/WaitingList.h"
#include <iostream>
#include <map>

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
void WaitingList::displayStatistics() const {
    std::cout << "Total waiting requests: "
              << requests.size() << '\n';

    if (requests.empty()) {
        std::cout << "No students are waiting.\n";
        return;
    }

    // Inspect a copy to preserve the original queue order.
    std::queue<WaitingRequest> copy = requests;
    std::map<std::string, std::size_t> counts;

    while (!copy.empty()) {
        ++counts[copy.front().resourceId];
        copy.pop();
    }

    std::cout << "Resources with waiting requests: "
              << counts.size() << '\n';

    std::size_t longestQueue = 0;

    for (const auto& entry : counts) {
        std::cout << "Resource " << entry.first
                  << ": " << entry.second
                  << " waiting request(s)\n";

        if (entry.second > longestQueue) {
            longestQueue = entry.second;
        }
    }

    std::cout << "Longest waiting list: "
              << longestQueue << " request(s)\n";

    std::cout << "Resource(s) with the longest waiting list:\n";

    for (const auto& entry : counts) {
        if (entry.second == longestQueue) {
            std::cout << "  " << entry.first << '\n';
        }
    }
}