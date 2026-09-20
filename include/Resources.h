// header file for resource class

// define the Resource class if it has not been defined yet
#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <string>

class Resource {

    private:
        std::string resourceID;
        std::string resourceName;
        std::string resourceType;
        std::string availabilityStatus;

    public:
        Resource(const std::string& id = "", const std::string& name = "", const std::string& type = "", const std::string& status = "");

        std::string getresourceID() const;
        std::string getresourceName() const;
        std::string getresourceType() const;
        std::string getavailabilityStatus() const;

        void display() const;

        // static method used to have one shared vector of resources for all instances of the Resource class
        static std::vector<Resource> resources;

        // load resources from a file
        static void loadResources(const std::string& filename);

        // display all resources
        static void displayAll();

        // search for a resource by ID
        static Resource* searchByID(const std::string& id);

        // sort resources by name, type, or availability status
        static void sortByName();
        static void sortByType();
        static void sortByStatus();

};

#endif