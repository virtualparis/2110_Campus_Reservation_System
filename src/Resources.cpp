// resource class

#include "Resources.h"
#include <algorithm> // used for sorting
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// defining the static vector of resources
vector<Resource> Resource::resources;

Resource::Resource(const string& id, const string& name, const string& type, const string& status) 
    : resourceID(id), resourceName(name), resourceType(type), availabilityStatus(status) {}

string Resource::getresourceID() const { return resourceID; }
string Resource::getresourceName() const { return resourceName; }
string Resource::getresourceType() const { return resourceType; }
string Resource::getavailabilityStatus() const { return availabilityStatus; }

// void display method to display the resource information
void Resource::display() const {
    cout << "Resource ID: " << resourceID << endl;
    cout << "Resource Name: " << resourceName << endl;
    cout << "Resource Type: " << resourceType << endl;
    cout << "Availability Status: " << availabilityStatus << endl;
}

// load resources from a file and add them to the resources vector
void Resource::loadResources(const string& filename) {
    ifstream file(filename);
    string line;

    // check if the file is open
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // if file is open, read each line for resource information
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, type, status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        // create a new resource object and add it to vector
        resources.emplace_back(id, name, type, status);
    }
}

// display all resources
void Resource::displayAll() {
    for (const auto& resource : resources) {
        resource.display();
        cout << "====================" << endl;
    }
}

// search for a resource by ID
Resource* Resource::searchByID(const string& id) {
    for (auto& resource : resources) {
        if (resource.getresourceID() == id)
            return &resource;
    }
    return nullptr;
}

// sort resources by name
void Resource::sortByName() {
    sort(resources.begin(), resources.end(), [](const Resource& a, const Resource& b) {
        return a.getresourceName() < b.getresourceName();
    });
}

// sort resources by type
void Resource::sortByType() {
    sort(resources.begin(), resources.end(), [](const Resource& a, const Resource& b) {
        return a.getresourceType() < b.getresourceType();
    });
}

// sort resources by availability status
void Resource::sortByStatus() {
    sort(resources.begin(), resources.end(), [](const Resource& a, const Resource& b) {
        return a.getavailabilityStatus() < b.getavailabilityStatus();
    });
}