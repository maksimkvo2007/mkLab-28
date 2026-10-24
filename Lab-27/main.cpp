#include <iostream>
#include <map>
#include <tuple>
#include <string>

using namespace std;

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
        
    }
}