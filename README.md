# Campus Resource Reservation System
Campus Resource Reservation System that allows users to reserve campus resources, manage waiting lists, track reservation history, and generate reports.
# Description
In this C++ program, students can make a reservation with their student name and student ID to reserve any of the following resources: study rooms, laptops, calculators, lab equipment, tutoring appointments. The system uses OOP principles to manage reservations with data read from an input file and user-input.
## Features
- **Create and Cancel Reservations** - users can create reservations for an available resource or cancel an existing reservation. If a resource is already reserved, then the user will be added to a waiting list. If a reservation is cancelled, then the resource is freed and automatically assigned to the next person in the waiting queue.
- **Search Reservation** - finds a reservation by ID using linear search.
- **Undo Cancellation** - restores the most recent cancellation, if the resource is available.
- **View and Sort Resources** - list every resource with its type and availability. Resources can be sorted by name, type, or availability through merge sort.
- **View Waiting List** - shows the queue of students waiting in a first-come, first-served order.
- **Generate Report** - prints active reservations, waiting list, cancellation history, and a resource utilization report.

## Data Structures and Algorithms
- **Linked List** - used for active reservation storage with dynamic sizing for frequent insertions and deletions
- **Queue** - used for resource waiting lists to implement a First Come, First serve process
- **Stack** - used for cancellation history and an undo functionality to implement a Last In, First out process
- **Vector** - used for fast traversal and sorting support for resource inventory
- **Linear Search** - used for small and unsorted lists, such as the reservations and resources files.
- **Merge Sort** - O(n log n), used to manually sort of unsorted data.

## Project Structure
project/
├── include/
│   ├── CancellationHistory.h
│   ├── Reservation.h
│   ├── ReservationManager.h
│   ├── Resources.h
│   └── WaitingList.h
├── src/
│   ├── main.cpp
│   ├── CancellationHistory.cpp
│   ├── Reservation.cpp
│   ├── ReservationManager.cpp
│   ├── Resources.cpp
│   └── WaitingList.cpp
├── data/
│   ├── resources.txt
│   └── reservations.txt
└── README.md

## Known Limitations
- Data is not saved to reservation or resource files, so changes only exist for the current run.
- Lookups are linear, so compilation is intended for small data.
