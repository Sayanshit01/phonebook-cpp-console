#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Contact {
public:
    string name;
    string phone;

    void input() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
    }

    void display() const {
        cout << "Name: " << name << "\nPhone: " << phone << "\n";
    }

    bool operator<(const Contact& other) const {
        return name < other.name;
    }
};

class Phonebook {
private:
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    void loadContacts() {
        contacts.clear();
        ifstream inFile(filename);
        if (inFile.is_open()) {
            Contact temp;
            while (getline(inFile, temp.name) && getline(inFile, temp.phone)) {
                contacts.push_back(temp);
            }
            inFile.close();
        }
    }

    void saveContacts() {
        ofstream outFile(filename);
        for (const auto& c : contacts) {
            outFile << c.name << "\n" << c.phone << "\n";
        }
        outFile.close();
    }

public:
    Phonebook() {
        loadContacts();
    }

    void addContact() {
        Contact c;
        c.input();
        contacts.push_back(c);
        saveContacts();
        cout << "Contact added successfully!\n";
    }

    void displayAll() const {
        if (contacts.empty()) {
            cout << "Phonebook is empty.\n";
            return;
        }
        cout << "\nAll Contacts:\n";
        for (const auto& c : contacts) {
            c.display();
            cout << "-----------------\n";
        }
    }

    void searchByName() {
        string searchName;
        cout << "Enter name to search: ";
        cin.ignore();
        getline(cin, searchName);
        bool found = false;
        for (const auto& c : contacts) {
            if (c.name == searchName) {
                c.display();
                found = true;
            }
        }
        if (!found)
            cout << "No contact found with that name.\n";
    }

    void deleteByName() {
        string nameToDelete;
        cout << "Enter name to delete: ";
        cin.ignore();
        getline(cin, nameToDelete);
        auto it = remove_if(contacts.begin(), contacts.end(),
                            [&nameToDelete](Contact& c) { return c.name == nameToDelete; });
        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            saveContacts();
            cout << "Contact deleted successfully.\n";
        } else {
            cout << "No contact found with that name.\n";
        }
    }

    void sortContacts() {
        sort(contacts.begin(), contacts.end());
        cout << "Contacts sorted by name.\n";
        saveContacts();
    }
};

// ------------------- MAIN -------------------

int main() {
    Phonebook pb;
    int choice;

    do {
        cout << "\n📱 PHONEBOOK MENU 📱\n";
        cout << "1. Add Contact\n";
        cout << "2. Display All Contacts\n";
        cout << "3. Search by Name\n";
        cout << "4. Delete by Name\n";
        cout << "5. Sort Contacts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: pb.addContact(); break;
        case 2: pb.displayAll(); break;
        case 3: pb.searchByName(); break;
        case 4: pb.deleteByName(); break;
        case 5: pb.sortContacts(); break;
        case 6: cout << "Exiting... Goodbye!\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
