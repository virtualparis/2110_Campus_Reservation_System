#include "Resources.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Resource> Resource::resources;

// merge sort comparison to return true if a is before b
using LessThan = bool (*)(const Resource&, const Resource&);

// helper to sort by resource name
bool byName(const Resource& a, const Resource& b) {
    return a.getresourceName() < b.getresourceName();
}

// helper to sort by resource type
bool byType(const Resource& a, const Resource& b) {
    return a.getresourceType() < b.getresourceType();
}

// helper to sort by availability status
bool byStatus(const Resource& a, const Resource& b) {
    return a.getavailabilityStatus() < b.getavailabilityStatus();
}

// merge sort for sorted data halves
void mergeRanges(std::vector<Resource>& list, std::size_t left, std::size_t mid, std::size_t right, LessThan lessThan) {
    std::vector<Resource> temp;
    temp.reserve(right - left);

    std::size_t i = left;
    std::size_t j = mid;

    while (i < mid && j < right) {
        if (lessThan(list[j], list[i])) {
            temp.push_back(list[j++]);
        }
        else {
            temp.push_back(list[i++]);
        }
    }
    while (i < mid) {
        temp.push_back(list[i++]);
    }
    while (j < right) {
        temp.push_back(list[j++]);
    }

    for (std::size_t k = 0; k < temp.size(); ++k) {
        list[left + k] = temp[k];
    }
}

// merge sort
void mergeSort(std::vector<Resource>& list, std::size_t left, std::size_t right, LessThan lessThan) {
    if (right - left < 2) {
        return;
    }

    std::size_t mid = left + (right - left) / 2;

    mergeSort(list, left, mid, lessThan);
    mergeSort(list, mid, right, lessThan);
    mergeRanges(list, left, mid, right, lessThan);
}

Resource::Resource(const std::string& id, const std::string& name,
                   const std::string& type, const std::string& status)
    : resourceID(id), resourceName(name),
      resourceType(type), availabilityStatus(status) {
}

std::string Resource::getresourceID() const {
    return resourceID;
}

std::string Resource::getresourceName() const {
    return resourceName;
}

std::string Resource::getresourceType() const {
    return resourceType;
}

std::string Resource::getavailabilityStatus() const {
    return availabilityStatus;
}

void Resource::setAvailabilityStatus(const std::string& status) {
    availabilityStatus = status;
}

void Resource::display() const {
    std::cout << "Resource ID: " << resourceID << '\n';
    std::cout << "Resource Name: " << resourceName << '\n';
    std::cout << "Resource Type: " << resourceType << '\n';
    std::cout << "Availability: " << availabilityStatus << '\n';
}

void Resource::loadResources(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening resource file: " << filename << '\n';
        return;
    }

    resources.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, type, status;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, status, '|');

        if (!id.empty()) {
            resources.emplace_back(id, name, type, status);
        }
    }
}

void Resource::displayAll() {
    if (resources.empty()) {
        std::cout << "No resources loaded.\n";
        return;
    }

    for (const auto& resource : resources) {
        resource.display();
        std::cout << "-------------------------\n";
    }
}

Resource* Resource::searchByID(const std::string& id) {
    for (auto& resource : resources) {
        if (resource.getresourceID() == id) {
            return &resource;
        }
    }
    return nullptr;
}

void Resource::sortByName() {
    mergeSort(resources, 0, resources.size(), byName);
}

void Resource::sortByType() {
    mergeSort(resources, 0, resources.size(), byType);
}

void Resource::sortByStatus() {
    mergeSort(resources, 0, resources.size(), byStatus);
}

int Resource::getReservationCount() const {
    return reservationCount;
}

void Resource::incrementReservationCount() {
    ++reservationCount;
}

void Resource::displayReport(int count) const {
    std::cout << "Resource ID: " << resourceID << '\n';
    std::cout << "Resource Name: " << resourceName << '\n';
    std::cout << "Resource Type: " << resourceType << '\n';
    std::cout << "Availability: " << availabilityStatus << '\n';
    std::cout << "Total Reservations: " << reservationCount << '\n';
    std::cout << "Active Reservations: " << count << '\n';
}
