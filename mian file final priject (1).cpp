#include <iostream>
#include <cstring>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

// ================================================
//  CLEAR SCREEN FUNCTION
// ================================================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ================================================
//  MODULE 1 - STATION MANAGEMENT
//  Arrays | Strings | Pointers
//  Linear Search | Binary Search | Recursion
// ================================================

#define MAX 100

struct Station {
    int id;
    char name[50];
    int platforms;
};

Station stations[MAX];
int stationCount = 0;

void sortByID() {
    for (int i = 0; i < stationCount - 1; i++)
        for (int j = 0; j < stationCount - i - 1; j++)
            if (stations[j].id > stations[j+1].id) {
                Station t = stations[j];
                stations[j] = stations[j+1];
                stations[j+1] = t;
            }
}

void addStation() {
    if (stationCount >= MAX) {
        cout << "\n  Station list is full!\n";
        return;
    }
    Station s;
    cout << "\n  Station ID     : "; cin >> s.id;
    cout << "  Station Name   : "; cin >> s.name;
    cout << "  Platform Count : "; cin >> s.platforms;
    stations[stationCount++] = s;
    sortByID();
    cout << "\n  Station added.\n";
}

void displayAll(int i) {
    if (i == stationCount) return;
    cout << "  " << setw(4) << left << stations[i].id
         << "  " << setw(22) << left << stations[i].name
         << "  " << stations[i].platforms << " platforms\n";
    displayAll(i + 1);
}

void readStations() {
    if (stationCount == 0) { cout << "\n  No stations added yet.\n"; return; }
    cout << "\n  ID    Name                    Platforms\n";
    cout << "  ----  ----------------------  ---------\n";
    displayAll(0);
}

void linearSearch() {
    char target[50];
    cout << "\n  Enter station name to search : "; cin >> target;
    for (int i = 0; i < stationCount; i++) {
        if (strcmp(stations[i].name, target) == 0) {
            cout << "\n  Found -> ID: " << stations[i].id
                 << "  Name: " << stations[i].name
                 << "  Platforms: " << stations[i].platforms << "\n";
            return;
        }
    }
    cout << "\n  Station not found.\n";
}

void binarySearch() {
    int id;
    cout << "\n  Enter station ID to search : "; cin >> id;
    int low = 0, high = stationCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (stations[mid].id == id) {
            cout << "\n  Found -> ID: " << stations[mid].id
                 << "  Name: " << stations[mid].name
                 << "  Platforms: " << stations[mid].platforms << "\n";
            return;
        }
        else if (stations[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    cout << "\n  Station not found.\n";
}

void updateStation() {
    int id;
    cout << "\n  Enter station ID to update : "; cin >> id;
    Station* ptr = NULL;
    for (int i = 0; i < stationCount; i++)
        if (stations[i].id == id) { ptr = &stations[i]; break; }
    if (ptr == NULL) { cout << "\n  Station not found.\n"; return; }
    cout << "  New Name         : "; cin >> ptr->name;
    cout << "  New Platform Count: "; cin >> ptr->platforms;
    sortByID();
    cout << "\n  Station updated.\n";
}

void deleteStation() {
    int id;
    cout << "\n  Enter station ID to delete : "; cin >> id;
    for (int i = 0; i < stationCount; i++) {
        if (stations[i].id == id) {
            for (int j = i; j < stationCount - 1; j++)
                stations[j] = stations[j+1];
            stationCount--;
            cout << "\n  Station deleted.\n";
            return;
        }
    }
    cout << "\n  Station not found.\n";
}

void module1Menu() {
    int ch;
    do {
        clearScreen();

        cout << "\n  ==============================\n";
        cout << "   MODULE 1 - Station Management\n";
        cout << "  ==============================\n";
        cout << "  1. Add Station\n";
        cout << "  2. Display All Stations\n";
        cout << "  3. Search by Name (Linear)\n";
        cout << "  4. Search by ID   (Binary)\n";
        cout << "  5. Update Station\n";
        cout << "  6. Delete Station\n";
        cout << "  0. Back\n";
        cout << "  ------------------------------\n";
        cout << "  Choice : ";
        cin >> ch;

        switch (ch) {
            case 1:
                clearScreen();
                addStation();
                system("pause");
                break;

            case 2:
                clearScreen();
                readStations();
                system("pause");
                break;

            case 3:
                clearScreen();
                linearSearch();
                system("pause");
                break;

            case 4:
                clearScreen();
                binarySearch();
                system("pause");
                break;

            case 5:
                clearScreen();
                updateStation();
                system("pause");
                break;

            case 6:
                clearScreen();
                deleteStation();
                system("pause");
                break;
        }

    } while (ch != 0);
}


// ================================================
//  MODULE 2 - TRAIN COACH MANAGEMENT
//  Doubly Linked List  -> Coaches
//  Singly Linked List  -> Passengers per Coach
//  Circular Linked List-> Boarding Waiting List
// ================================================

struct Passenger {
    char name[50];
    int  seat;
    Passenger* next;
};

struct Coach {
    int   number;
    int   capacity;
    Passenger* passengerHead;
    Coach* prev;
    Coach* next;
};

struct WaitNode {
    char name[50];
    WaitNode* next;
};

Coach*   coachHead  = NULL;
Coach*   coachTail  = NULL;
WaitNode* waitTail  = NULL;

Coach* findCoach(int num) {
    Coach* c = coachHead;
    while (c != NULL) {
        if (c->number == num) return c;
        c = c->next;
    }
    return NULL;
}

void addCoach() {
    Coach* c  = new Coach();
    cout << "\n  Coach Number : "; cin >> c->number;
    cout << "  Capacity     : "; cin >> c->capacity;
    c->passengerHead = NULL;
    c->prev = NULL;
    c->next = NULL;
    if (coachHead == NULL)
        coachHead = coachTail = c;
    else {
        c->prev = coachTail;
        coachTail->next = c;
        coachTail = c;
    }
    cout << "\n  Coach added.\n";
}

void showCoachesForward() {
    if (coachHead == NULL) { cout << "\n  No coaches yet.\n"; return; }
    cout << "\n  Coaches (Front to Rear):\n";
    Coach* c = coachHead;
    while (c != NULL) {
        cout << "  Coach " << c->number << "  |  Capacity: " << c->capacity << "\n";
        c = c->next;
    }
}

void showCoachesBackward() {
    if (coachTail == NULL) { cout << "\n  No coaches yet.\n"; return; }
    cout << "\n  Coaches (Rear to Front):\n";
    Coach* c = coachTail;
    while (c != NULL) {
        cout << "  Coach " << c->number << "  |  Capacity: " << c->capacity << "\n";
        c = c->prev;
    }
}

void updateCoach() {
    int num;
    cout << "\n  Coach number to update : "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    cout << "  New Coach Number : "; cin >> c->number;
    cout << "  New Capacity     : "; cin >> c->capacity;
    cout << "\n  Coach updated.\n";
}

void deleteCoach() {
    int num;
    cout << "\n  Coach number to delete : "; cin >> num;
    Coach* c = coachHead;
    while (c != NULL && c->number != num) c = c->next;
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    if (c->prev != NULL) c->prev->next = c->next; else coachHead = c->next;
    if (c->next != NULL) c->next->prev = c->prev; else coachTail = c->prev;
    delete c;
    cout << "\n  Coach deleted.\n";
}

void addPassenger() {
    int num;
    cout << "\n  Coach number : "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    Passenger* p = new Passenger();
    cout << "  Passenger Name : "; cin >> p->name;
    cout << "  Seat Number    : "; cin >> p->seat;
    p->next = NULL;
    if (c->passengerHead == NULL)
        c->passengerHead = p;
    else {
        Passenger* t = c->passengerHead;
        while (t->next != NULL) t = t->next;
        t->next = p;
    }
    cout << "\n  Passenger added.\n";
}

void showPassengers() {
    int num;
    cout << "\n  Coach number : "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    if (c->passengerHead == NULL) { cout << "\n  No passengers in this coach.\n"; return; }
    cout << "\n  Passengers in Coach " << num << ":\n";
    Passenger* p = c->passengerHead;
    while (p != NULL) {
        cout << "  Name: " << p->name << "  Seat: " << p->seat << "\n";
        p = p->next;
    }
}

void updatePassenger() {
    int num;
    cout << "\n  Coach number : "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    char pname[50];
    cout << "  Passenger name to update : "; cin >> pname;
    Passenger* p = c->passengerHead;
    while (p != NULL && strcmp(p->name, pname) != 0) p = p->next;
    if (p == NULL) { cout << "\n  Passenger not found.\n"; return; }
    cout << "  New Name        : "; cin >> p->name;
    cout << "  New Seat Number : "; cin >> p->seat;
    cout << "\n  Passenger updated.\n";
}

void deletePassenger() {
    int num;
    cout << "\n  Coach number : "; cin >> num;
    Coach* c = findCoach(num);
    if (c == NULL) { cout << "\n  Coach not found.\n"; return; }
    char pname[50];
    cout << "  Passenger name to delete : "; cin >> pname;
    Passenger* p = c->passengerHead;
    Passenger* prev = NULL;
    while (p != NULL && strcmp(p->name, pname) != 0) { prev = p; p = p->next; }
    if (p == NULL) { cout << "\n  Passenger not found.\n"; return; }
    if (prev == NULL) c->passengerHead = p->next;
    else prev->next = p->next;
    delete p;
    cout << "\n  Passenger removed.\n";
}

void addToWaiting() {
    WaitNode* w = new WaitNode();
    cout << "\n  Passenger name : "; cin >> w->name;
    w->next = NULL;
    if (waitTail == NULL) { waitTail = w; waitTail->next = waitTail; }
    else { w->next = waitTail->next; waitTail->next = w; waitTail = w; }
    cout << "\n  Added to waiting list.\n";
}

void showWaiting() {
    if (waitTail == NULL) { cout << "\n  Waiting list is empty.\n"; return; }
    cout << "\n  Boarding Waiting List:\n";
    WaitNode* start = waitTail->next;
    WaitNode* t = start;
    int i = 1;
    do { cout << "  " << i++ << ". " << t->name << "\n"; t = t->next; } while (t != start);
}

void removeFromWaiting() {
    if (waitTail == NULL) { cout << "\n  Waiting list is empty.\n"; return; }
    WaitNode* front = waitTail->next;
    cout << "\n  Removed: " << front->name << "\n";
    if (front == waitTail) { delete front; waitTail = NULL; }
    else { waitTail->next = front->next; delete front; }
}

void module2Menu() {
    int ch;
    do {
        clearScreen();

        cout << "\n  ==============================\n";
        cout << "   MODULE 2 - Coach Management\n";
        cout << "  ==============================\n";
        cout << "  1. Add Coach\n";
        cout << "  2. Show Coaches Forward\n";
        cout << "  3. Show Coaches Backward\n";
        cout << "  4. Update Coach\n";
        cout << "  5. Delete Coach\n";
        cout << "  6. Add Passenger\n";
        cout << "  7. Show Passengers\n";
        cout << "  8. Update Passenger\n";
        cout << "  9. Delete Passenger\n";
        cout << "  10. Add to Waiting\n";
        cout << "  11. Show Waiting\n";
        cout << "  12. Remove Waiting\n";
        cout << "  0. Back\n";
        cout << "  Choice : ";
        cin >> ch;

        clearScreen();

        switch (ch) {
            case 1: addCoach(); system("pause"); break;
            case 2: showCoachesForward(); system("pause"); break;
            case 3: showCoachesBackward(); system("pause"); break;
            case 4: updateCoach(); system("pause"); break;
            case 5: deleteCoach(); system("pause"); break;
            case 6: addPassenger(); system("pause"); break;
            case 7: showPassengers(); system("pause"); break;
            case 8: updatePassenger(); system("pause"); break;
            case 9: deletePassenger(); system("pause"); break;
            case 10: addToWaiting(); system("pause"); break;
            case 11: showWaiting(); system("pause"); break;
            case 12: removeFromWaiting(); system("pause"); break;
        }

    } while (ch != 0);
}


// ================================================
//  MODULE 3 - TICKETING SYSTEM
//  Stack        -> Booking History (LIFO)
//  Queue        -> Ticket Counter  (FIFO)
//  Circular Queue -> Platform Allocation
// ================================================

#define SMAX 100
#define CMAX 10

struct Ticket {
    char passenger[50];
    char station[50];
    int  fare;
};

Ticket stk[SMAX];
int    top = -1;

struct QNode {
    char name[50];
    QNode* next;
};
QNode* qFront = NULL;
QNode* qRear  = NULL;

char   cq[CMAX][50];
int    cf = -1, cr = -1;

void bookTicket() {
    if (top >= SMAX - 1) { cout << "\n  Stack full.\n"; return; }
    Ticket t;
    cout << "\n  Passenger Name : "; cin >> t.passenger;
    cout << "  Station        : "; cin >> t.station;
    cout << "  Fare           : "; cin >> t.fare;
    stk[++top] = t;
    cout << "\n  Ticket booked.\n";
}

void peekTicket() {
    if (top == -1) { cout << "\n  No bookings yet.\n"; return; }
    cout << "\n  Last Booking:\n";
    cout << "  Passenger : " << stk[top].passenger << "\n";
    cout << "  Station   : " << stk[top].station   << "\n";
    cout << "  Fare      : " << stk[top].fare      << "\n";
}

void showHistory() {
    if (top == -1) { cout << "\n  No booking history.\n"; return; }
    cout << "\n  Booking History (latest first):\n";
    for (int i = top; i >= 0; i--)
        cout << "  " << stk[i].passenger << "  ->  " << stk[i].station << "  Rs." << stk[i].fare << "\n";
}

void cancelTicket() {
    if (top == -1) { cout << "\n  No bookings to cancel.\n"; return; }
    cout << "\n  Cancelled: " << stk[top].passenger << "\n";
    top--;
}

void enqueue() {
    QNode* n = new QNode();
    cout << "\n  Passenger name : "; cin >> n->name;
    n->next = NULL;
    if (qRear == NULL) qFront = qRear = n;
    else { qRear->next = n; qRear = n; }
    cout << "\n  Added to counter queue.\n";
}

void showQueue() {
    if (qFront == NULL) { cout << "\n  Counter queue is empty.\n"; return; }
    cout << "\n  Ticket Counter Queue:\n";
    QNode* t = qFront; int i = 1;
    while (t != NULL) { cout << "  " << i++ << ". " << t->name << "\n"; t = t->next; }
}

void updateQueuePassenger() {
    if (qFront == NULL) { cout << "\n  Queue is empty.\n"; return; }
    char old[50];
    cout << "\n  Enter passenger name to update : "; cin >> old;
    QNode* t = qFront;
    while (t != NULL) {
        if (strcmp(t->name, old) == 0) {
            cout << "  New name : "; cin >> t->name;
            cout << "\n  Updated.\n"; return;
        }
        t = t->next;
    }
    cout << "\n  Passenger not found.\n";
}

void dequeue() {
    if (qFront == NULL) { cout << "\n  Queue is empty.\n"; return; }
    cout << "\n  Serving: " << qFront->name << "\n";
    QNode* t = qFront;
    qFront = qFront->next;
    if (qFront == NULL) qRear = NULL;
    delete t;
}

void addPlatform() {
    if (cf == 0 && cr == CMAX - 1) { cout << "\n  Platform queue full.\n"; return; }
    if (cf == -1) cf = cr = 0; else cr = (cr + 1) % CMAX;
    cout << "\n  Platform name : "; cin >> cq[cr];
    cout << "\n  Platform added.\n";
}

void showPlatforms() {
    if (cf == -1) { cout << "\n  No platforms.\n"; return; }
    cout << "\n  Platform Queue:\n";
    int i = cf, cnt = 0;
    while (true) {
        cout << "  Platform: " << cq[i] << "\n";
        if (i == cr) break;
        i = (i + 1) % CMAX;
        if (++cnt > CMAX) break;
    }
}

void updatePlatform() {
    if (cf == -1) { cout << "\n  No platforms.\n"; return; }
    char old[50];
    cout << "\n  Platform name to update : "; cin >> old;
    int i = cf;
    while (true) {
        if (strcmp(cq[i], old) == 0) {
            cout << "  New platform name : "; cin >> cq[i];
            cout << "\n  Updated.\n"; return;
        }
        if (i == cr) break;
        i = (i + 1) % CMAX;
    }
    cout << "\n  Platform not found.\n";
}

void removePlatform() {
    if (cf == -1) { cout << "\n  No platforms.\n"; return; }
    cout << "\n  Removed: " << cq[cf] << "\n";
    if (cf == cr) cf = cr = -1; else cf = (cf + 1) % CMAX;
}

void module3Menu() {
    int ch;
    do {
        clearScreen();

        cout << "\n  ==============================\n";
        cout << "   MODULE 3 - Ticketing System\n";
        cout << "  ==============================\n";
        cout << "  1. Book Ticket\n";
        cout << "  2. Peek Ticket\n";
        cout << "  3. Show History\n";
        cout << "  4. Cancel Ticket\n";
        cout << "  5. Enqueue\n";
        cout << "  6. Show Queue\n";
        cout << "  7. Update Queue\n";
        cout << "  8. Dequeue\n";
        cout << "  9. Add Platform\n";
        cout << "  10. Show Platforms\n";
        cout << "  11. Update Platform\n";
        cout << "  12. Remove Platform\n";
        cout << "  0. Back\n";
        cout << "  Choice : ";
        cin >> ch;

        clearScreen();

        switch (ch) {
            case 1: bookTicket(); system("pause"); break;
            case 2: peekTicket(); system("pause"); break;
            case 3: showHistory(); system("pause"); break;
            case 4: cancelTicket(); system("pause"); break;
            case 5: enqueue(); system("pause"); break;
            case 6: showQueue(); system("pause"); break;
            case 7: updateQueuePassenger(); system("pause"); break;
            case 8: dequeue(); system("pause"); break;
            case 9: addPlatform(); system("pause"); break;
            case 10: showPlatforms(); system("pause"); break;
            case 11: updatePlatform(); system("pause"); break;
            case 12: removePlatform(); system("pause"); break;
        }

    } while (ch != 0);
}


// ================================================
//  MAIN MENU
// ================================================

int main() {
    int ch;
    do {
        cout << "\n  ==============================\n";
        cout << "   METRO RAIL MANAGEMENT SYSTEM\n";
        cout << "   Riphah International University\n";
        cout << "   Data Structures - 3rd Semester\n";
        cout << "  ==============================\n";
        cout << "  1. Station Management\n";
        cout << "  2. Train Coach Management\n";
        cout << "  3. Ticketing System\n";
        cout << "  0. Exit\n";
        cout << "  ------------------------------\n";
        cout << "  Choice : "; cin >> ch;
        switch (ch) {
            case 1: module1Menu(); break;
            case 2: module2Menu(); break;
            case 3: module3Menu(); break;
            case 0: cout << "\n  Goodbye!\n\n"; break;
            default: cout << "\n  Invalid choice.\n";
        }
    } while (ch != 0);
    return 0;
}
