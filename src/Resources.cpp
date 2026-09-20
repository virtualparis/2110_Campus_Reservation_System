#include "Resources.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<Resource> Resource::resources;

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
    std::sort(resources.begin(), resources.end(),
              [](const Resource& a, const Resource& b) {
                  return a.getresourceName() < b.getresourceName();
              });
}

void Resource::sortByType() {
    std::sort(resources.begin(), resources.end(),
              [](const Resource& a, const Resource& b) {
                  return a.getresourceType() < b.getresourceType();
              });
}

void Resource::sortByStatus() {
    std::sort(resources.begin(), resources.end(),
              [](const Resource& a, const Resource& b) {
                  return a.getavailabilityStatus() <
                         b.getavailabilityStatus();
              });
}