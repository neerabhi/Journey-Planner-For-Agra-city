#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

class Journey {
private:
    const int numStations = 6;  // Number of stations
    const int numTouristPlaces = 5;  // Number of tourist places
    const double fareThreshold1 = 2.0;  // Fare thresholds for different fare levels
    const double fareThreshold2 = 4.0;
    const double fare1 = 20.0;  // Fare rates for different distances
    const double fare2 = 25.0;
    const double fare3 = 30.0;

    string stations[6] = {"Bus Stand", "Railway Station", "Airport", "Metro Station", "Tourist Place 1", "Tourist Place 2"};  // Names of stations
    double distances[6][6];  // Distance matrix between stations
    bool seatAvailability[40];  // Availability of seats for booking
    bool ticketAvailability[5];  // Availability of tickets for tourist places

public:
    Journey() {
        initializeGraph();
        initializeSeats();
        initializeTickets();
    }

    // Display the main menu and get user choice
    int Choice() {
        int x;
        cout << "Please enter the number of your choice" << endl;
        cout << "1. List the stations" << endl;
        cout << "2. Find the shortest route between two stations" << endl;
        cout << "3. Find the fare between two stations" << endl;
        cout << "4. Book seats in the bus" << endl;
        cout << "5. List tourist places in Agra" << endl;
        cout << "6. Book ticket for tourist place" << endl;
        cout << "7. Exit" << endl;
        cin >> x;
        return x;
    }

    // Initialize all seats as available
    void initializeSeats() {
        for (int i = 0; i < 40; ++i) {
            seatAvailability[i] = true;
        }
    }

    // Initialize all tickets as available
    void initializeTickets() {
        for (int i = 0; i < 5; ++i) {
            ticketAvailability[i] = true;
        }
    }

    // Initialize the distance matrix with example distances
    void initializeGraph() {
        // Initialize distances between stations
        // For simplicity, assume direct connections for stations
        // Example distances - replace with actual distances between stations
        setDistance(0, 1, 5.0);
        setDistance(0, 2, 8.0);
        setDistance(0, 3, 3.0);
        setDistance(1, 2, 6.0);
        setDistance(1, 3, 4.0);
        setDistance(2, 3, 7.0);
        setDistance(4, 0, 10.0); // Example distance to Tourist Place 1
        setDistance(5, 0, 12.0); // Example distance to Tourist Place 2
    }

    // Set distance between two stations (bidirectional)
    void setDistance(int source, int destination, double distance) {
        distances[source][destination] = distance;
        distances[destination][source] = distance; // Assume bidirectional for simplicity
    }

    // List all stations
    void listStations() {
        cout << "List of stations:" << endl;
        for (int i = 0; i < numStations; ++i) {
            cout << i + 1 << ". " << stations[i] << endl;
        }
    }

    // Prompt user for source and destination stations, then find shortest route using Dijkstra's algorithm
    void findingPath() {
        listStations();
        int source, destination;
        cout << "Enter the source station (1-" << numStations << "): ";
        cin >> source;
        cout << "Enter the destination station (1-" << numStations << "): ";
        cin >> destination;

        if (source >= 1 && source <= numStations && destination >= 1 && destination <= numStations) {
            dijkstra(source - 1, destination - 1);
        } else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    // Dijkstra's algorithm to find shortest path between two stations
    void dijkstra(int source, int destination) const {
        double distance[numStations];
        bool visited[numStations];
        int predecessor[numStations];

        // Initialize distances, visited status, and predecessors
        for (int i = 0; i < numStations; ++i) {
            distance[i] = numeric_limits<double>::infinity();
            visited[i] = false;
            predecessor[i] = -1;
        }

        distance[source] = 0.0;

        // Find shortest path
        for (int count = 0; count < numStations - 1; ++count) {
            int u = minDistance(distance, visited);
            visited[u] = true;

            for (int v = 0; v < numStations; ++v) {
                if (!visited[v] && distances[u][v] != -1 && distance[u] + distances[u][v] < distance[v]) {
                    distance[v] = distance[u] + distances[u][v];
                    predecessor[v] = u;
                }
            }
        }

        // Print shortest path and total distance
        printShortestPath(source, destination, distance, predecessor);
    }

    // Find the index of the station with the minimum distance value
    int minDistance(const double distance[], const bool visited[]) const {
        double minDist = numeric_limits<double>::infinity();
        int minIndex = -1;

        for (int i = 0; i < numStations; ++i) {
            if (!visited[i] && distance[i] < minDist) {
                minDist = distance[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    // Print the shortest path from source to destination station
    void printShortestPath(int source, int destination, const double distance[], const int predecessor[]) const {
        cout << "Shortest path from " << stations[source] << " to " << stations[destination] << ":" << endl;
        cout << "Total Distance: " << fixed << setprecision(2) << distance[destination] << " km" << endl;

        // Print the actual path
        cout << "The shortest path is: " << stations[source];
        printPath(destination, source, predecessor);
        cout << endl;
    }

    // Recursively print the path from source to current station
    void printPath(int current, int source, const int predecessor[]) const {
        if (current == source) {
            return;
        }

        printPath(predecessor[current], source, predecessor);
        cout << " -> " << stations[current];
    }

    // Calculate fare between two stations based on distance
    void fare() {
        listStations();
        int source, destination;
        cout << "Enter the source station (1-" << numStations << "): ";
        cin >> source;
        cout << "Enter the destination station (1-" << numStations << "): ";
        cin >> destination;

        if (source >= 1 && source <= numStations && destination >= 1 && destination <= numStations) {
            double distance = distances[source - 1][destination - 1];
            calculateAndPrintFare(distance);
        } else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    // Calculate and print fare based on distance
    void calculateAndPrintFare(double distance) const {
        double fare;
        if (distance <= fareThreshold1)
            fare = fare1;
        else if (distance <= fareThreshold2)
            fare = fare2;
        else
            fare = fare3;

        cout << "Total Distance: " << fixed << setprecision(2) << distance << " km" << endl;
        cout << "Fare: Rs. " << fare << endl;
    }

    // Book seats in the bus
    void Book() {
        char moreSeatsChoice;
        do {
            cout << "\nEnter your Name: ";
            string name;
            cin >> name;

            cout << "Enter your Age: ";
            int age;
            cin >> age;

            cout << "Enter your Gender (M/F): ";
            char gender;
            cin >> gender;

            cout << "Enter your Phone Number: ";
            long long phoneNumber;
            cin >> phoneNumber;

            cout << "Enter the seat number you want to reserve (1-40): ";
            int seatNumber;
            cin >> seatNumber;

            int bookedSeat = reserveSeat(age, gender, seatNumber);
            if (bookedSeat != -1) {
                cout << "\nSeat booked successfully!\n";
                cout << "Name: " << name << ", Seat Number: " << bookedSeat << endl;
            } else {
                cout << "\nSorry, the specified seat is not available or doesn't match your criteria.\n";
            }

            cout << "Remaining available seats: " << countAvailableSeats() << endl;

            cout << "\nDo you want to book more seats? Type 'y' if yes: ";
            cin >> moreSeatsChoice;

        } while (moreSeatsChoice == 'Y' || moreSeatsChoice == 'y');
    }

    // Reserve a seat in the bus based on age, gender, and seat number criteria
    int reserveSeat(int age, char gender, int seatNumber) {
        if (seatNumber < 1 || seatNumber > 40 || !seatAvailability[seatNumber - 1]) {
            return -1;
        }

        int index = seatNumber - 1;
        if (seatNumber == 1 || seatNumber == 2) {
            if (age < 60) {
                cout << "\n~Seats 1 and 2 are reserved for people aged 60 and above~";
                return -1;
            }
        } else if (seatNumber == 3 || seatNumber == 4) {
            if (!(gender == 'F' || gender == 'f')) {
                cout << "\n~Seats 3 and 4 are reserved for females~";
                return -1;
            }
        }

        seatAvailability[index] = false;
        return seatNumber; // Seat booked successfully
    }

    // Count the number of available seats
    int countAvailableSeats() const {
        int count = 0;
        for (int i = 0; i < 40; ++i) {
            if (seatAvailability[i]) {
                count++;
            }
        }
        return count;
    }

    // List tourist places in Agra
    void listTouristPlaces() const {
        cout << "List of tourist places in Agra:" << endl;
        cout << "1. Taj Mahal" << endl;
        cout << "2. Agra Fort" << endl;
        cout << "3. Fatehpur Sikri" << endl;
        cout << "4. Itmad-ud-Daula's Tomb" << endl;
        cout << "5. Akbar's Tomb, Sikandra" << endl;
    }

    // Book ticket for a tourist place in Agra
    void bookTouristPlaceTicket() {
        listTouristPlaces();
        int choice;
        cout << "Enter the number of the tourist place you want to visit (1-" << numTouristPlaces << "): ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookTicket("Taj Mahal");
                break;
            case 2:
                bookTicket("Agra Fort");
                break;
            case 3:
                bookTicket("Fatehpur Sikri");
                break;
            case 4:
                bookTicket("Itmad-ud-Daula's Tomb");
                break;
            case 5:
                bookTicket("Akbar's Tomb, Sikandra");
                break;
            default:
                cout << "Invalid choice. Please choose a valid tourist place." << endl;
                break;
        }
    }

    // Book ticket for a tourist place (placeholder)
    void bookTicket(const string& place) {
        int placeIndex = placeNumberToIndex(place);
        if (placeIndex != -1 && ticketAvailability[placeIndex]) {
            ticketAvailability[placeIndex] = false;
            cout << "Booking ticket for " << place << "..." << endl;
            cout << "Ticket booked successfully for " << place << "!" << endl;
        } else {
            cout << "Sorry, tickets for " << place << " are currently unavailable." << endl;
        }
    }

    // Convert tourist place number to array index
    int placeNumberToIndex(const string& place) const {
        if (place == "Taj Mahal") {
            return 0;
        } else if (place == "Agra Fort") {
            return 1;
        } else if (place == "Fatehpur Sikri") {
            return 2;
        } else if (place == "Itmad-ud-Daula's Tomb") {
            return 3;
        } else if (place == "Akbar's Tomb, Sikandra") {
            return 4;
        } else {
            return -1; // Invalid place
        }
    }
};

int main() {
    Journey j;
    int x;
    char a;
    cout << "**WELCOME TO THE JOURNEY PLANNER**\n";
    do {
        x = j.Choice();
        switch (x) {
            case 1:
                j.listStations();
                break;
            case 2:
                j.findingPath();
                break;
            case 3:
                j.fare();
                break;
            case 4:
                j.Book();
                break;
            case 5:
                j.listTouristPlaces();
                break;
            case 6:
                j.bookTouristPlaceTicket();
                break;
            case 7:
                cout << "\n**THANK YOU FOR USING OUR SERVICE**\n";
                return 0;
            default:
                cout << "Invalid input. Please enter a valid option." << endl;
                break;
        }
        cout << "\nDo you want to perform more operations? Type 'y' if yes: ";
        cin >> a;
    } while (a == 'Y' || a == 'y');
    cout << "\n**THANK YOU FOR USING OUR SERVICE**\n";
    return 0;
}
