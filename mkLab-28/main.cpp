#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <algorithm> 
#include <numeric>   
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("mkLab-28/names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (i < SZ_NAMES && fin >> names[i]) {
        i++;
    }
    fin.close();

    ifstream fin1("mkLab-28/colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (i < SZ_COLORS && fin1 >> colors[i]) {
        i++;
    }
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    // Goat Manager 3001 Engine
    bool again = true;
    while (again) {
        int sel = main_menu();
        switch (sel) {
            case 1: 
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2: 
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3: 
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: 
                cout << "Printing all goat names:\n";
                for_each(trip.begin(), trip.end(), [](const Goat& g) { cout << g.get_name() << " "; });
                cout << "\n";
                break;
            case 5: {
                int over10 = count_if(trip.begin(), trip.end(), [](const Goat& g) { return g.get_age() > 10; });
                cout << "Goats older than 10: " << over10 << "\n";
                break;
            }
            case 6: {
                bool hasRed = any_of(trip.begin(), trip.end(), [](const Goat& g) { return g.get_color() == "Red"; });
                cout << (hasRed ? "There is at least one Red goat.\n" : "No Red goats found.\n");
                break;
            }
            case 7: {
                bool allYoung = all_of(trip.begin(), trip.end(), [](const Goat& g) { return g.get_age() < 20; });
                cout << (allYoung ? "All goats are under 20.\n" : "Some goats are 20 or older.\n");
                break;
            }
            case 8: {
                auto oldest = max_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
                if (oldest != trip.end()) cout << "Oldest goat is " << oldest->get_name() << " at age " << oldest->get_age() << "\n";
                break;
            }
            case 9: {
                auto youngest = min_element(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
                if (youngest != trip.end()) cout << "Youngest goat is " << youngest->get_name() << " at age " << youngest->get_age() << "\n";
                break;
            }
            case 10: {
                int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g) { return sum + g.get_age(); });
                cout << "Total combined age of all goats: " << totalAge << "\n";
                break;
            }
            case 11: 
                cout << "Reversing the list order...\n";
                reverse(trip.begin(), trip.end());
                cout << "List reversed. Select '3' to view the new order.\n";
                break;
            case 12: 
                cout << "Quitting...\n";
                again = false;
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
    }
    return 0;
}

int main_menu() {
    cout << "\n*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Show all names (for_each)\n";
    cout << "[5] Count goats over 10 (count_if)\n";
    cout << "[6] Check for Red goats (any_of)\n";
    cout << "[7] Check if all under 20 (all_of)\n";
    cout << "[8] Find oldest goat (max_element)\n";
    cout << "[9] Find youngest goat (min_element)\n";
    cout << "[10] Get total age (accumulate)\n";
    cout << "[11] Reverse list order (reverse)\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trip) {
    int i = 1;
    for (list<Goat>::iterator it = trip.begin(); it != trip.end(); ++it) {
        cout << "[" << i++ << "] " 
             << it->get_name() 
             << " (" << it->get_age() 
             << ", " << it->get_color() << ")\n";
    }
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}