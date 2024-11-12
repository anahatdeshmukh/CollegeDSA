#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Event {
    string name;
    string date;
    string time;
    int ticketPrice;
    int ticketsSold;
};

int main() {
    Event events[10];
    int eventCount = 0;
    int totalRevenue = 0;

    while (true) {
        cout << "\nEvent Management App\n";
        cout << "1. Add Event\n";
        cout << "2. Display Events\n";
        cout << "3. Purchase Ticket\n";
        cout << "4. Make ICS File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (eventCount < 10) {
                cout << "Enter event name: ";
                cin.ignore();
                getline(cin, events[eventCount].name);
                cout << "Enter event date (YYYY-MM-DD): ";
                getline(cin, events[eventCount].date);
                cout << "Enter event time (HH:MM): ";
                getline(cin, events[eventCount].time);
                cout << "Enter ticket price: ";
                cin >> events[eventCount].ticketPrice;
                events[eventCount].ticketsSold = 0;
                eventCount++;
            } else {
                cout << "Event list is full.\n";
            }
        } 
        else if (choice == 2) {
            if (eventCount == 0) {
                cout << "No events available.\n";
            } else {
                for (int i = 0; i < eventCount; i++) {
                    cout << "\nEvent " << i + 1 << ":\n";
                    cout << "Name: " << events[i].name << "\n";
                    cout << "Date: " << events[i].date << "\n";
                    cout << "Time: " << events[i].time << "\n";
                    cout << "Ticket Price: " << events[i].ticketPrice << "\n";
                    cout << "Tickets Sold: " << events[i].ticketsSold << "\n";
                }
            }
        } 
        else if (choice == 3) {
            int eventId;
            cout << "Enter event number to purchase ticket: ";
            cin >> eventId;
            eventId--;  // Convert to 0-based index

            if (eventId >= 0 && eventId < eventCount) {
                events[eventId].ticketsSold++;
                totalRevenue += events[eventId].ticketPrice;
                cout << "Ticket purchased successfully for event: " << events[eventId].name << "\n";
            } else {
                cout << "Invalid event number.\n";
            }
        } 
        else if (choice == 4) {
            int eventId;
            cout << "Enter event number to create ICS file: ";
            cin >> eventId;
            eventId--;  // Convert to 0-based index

            if (eventId >= 0 && eventId < eventCount) {
                ofstream icsFile(events[eventId].name + ".ics");
                if (icsFile.is_open()) {
                    icsFile << "BEGIN:VCALENDAR\n";
                    icsFile << "VERSION:2.0\n";
                    icsFile << "BEGIN:VEVENT\n";
                    icsFile << "SUMMARY:" << events[eventId].name << "\n";
                    icsFile << "DTSTART:" << events[eventId].date << "T" << events[eventId].time << "00\n";
                    icsFile << "DTEND:" << events[eventId].date << "T" << events[eventId].time << "30\n"; // 30 mins event duration
                    icsFile << "END:VEVENT\n";
                    icsFile << "END:VCALENDAR\n";
                    icsFile.close();
                    cout << "ICS file created successfully for event: " << events[eventId].name << "\n";
                } else {
                    cout << "Error creating ICS file.\n";
                }
            } else {
                cout << "Invalid event number.\n";
            }
        } 
        else if (choice == 5) {
            cout << "Exiting... Total revenue from ticket sales: " << totalRevenue << "\n";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
