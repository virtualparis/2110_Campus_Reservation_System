#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>

class Resource {
private:
    std::string resourceID;
    std::string resourceName;
    std::string resourceType;
    std::string availabilityStatus;

public:
    Resource(const std::string& id = "",
             const std::string& name = "",
             const std::string& type = "",
             const std::string& status = "");

    std::string getresourceID() const;
    std::string getresourceName() const;
    std::string getresourceType() const;
    std::string getavailabilityStatus() const;

    void setAvailabilityStatus(const std::string& status);
    void display() const;

    static std::vector<Resource> resources;

    static void loadResources(const std::string& filename);
    static void displayAll();
    static Resource* searchByID(const std::string& id);

    static void sortByName();
    static void sortByType();
    static void sortByStatus();
};

#endif