#include <iostream>
#include <map>
#include <tuple>
#include <string>
using namespace std;

void printMap(const map<string, tuple<int, string, string>>& vmap) {
    cout << "\nVillager details:\n";
    for (auto const& v : vmap) {
        // v.first is the string key (name)
        // v.second is the tuple
        cout << v.first << " ["
             << get<0>(v.second) << ", "
             << get<1>(v.second) << ", "
             << get<2>(v.second) << "]\n";
    }
    cout << "\n";
}

int main (){

    map<string, tuple<int, string, string>> vmap;
    
    int choice = 0;
    string name, species, phrase;
    int level;

    while (choice != 6) {
        cout << "1. Add Villager\n";
        cout << "2. Delete Villager\n";
        cout << "3. Increase Friendship\n";
        cout << "4. Decrease Friendship\n";
        cout << "5. Search for Villager\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Villager name: ";
            cin >> name;
            cout << "Friendship level: ";
            cin >> level;
            cout << "Species: ";
            cin >> species;
            cout << "Catchphrase: ";
            cin.ignore(); 
            getline(cin, phrase);
            
            // Add to the map
            vmap[name] = make_tuple(level, species, phrase);
            cout << name << " added.\n";
            printMap(vmap);
        }
        else if (choice == 2) {
            cout << "Villager name to delete: ";
            cin >> name;
            vmap.erase(name);
            printMap(vmap);
        }

        else if (choice == 3) {
            cout << "Villager name: ";
            cin >> name;
            if (vmap.count(name) > 0) { // Check if they exist first
                if (get<0>(vmap[name]) < 10) {
                    get<0>(vmap[name])++; // Increase level
                }
            } else {
                cout << "Villager not found.\n";
            }
            printMap(vmap);
        }



    }
}