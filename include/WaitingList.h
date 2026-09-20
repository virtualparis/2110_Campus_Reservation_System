#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <string>

struct WaitingRequest {
    int studentId;
    std::string studentName;
    std::string resourceId;
};

class WaitingList {
private:
    std::queue<WaitingRequest> requests;

public:
    void addStudent(const WaitingRequest& request);
    bool removeNextStudent(WaitingRequest& request);

    bool removeNextStudentForResource(
        const std::string& resourceId,
        WaitingRequest& request);

    void displayWaitingList() const;
    bool isEmpty() const;
};

#endif
