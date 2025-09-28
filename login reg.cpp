#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class User {
private:
    string username;
    string password;

public:
    User(string u = "", string p = "") {
        username = u;
        password = p;
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
    void saveToFile() {
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
        }
    }
    static bool authenticate(string uname, string pass) {
        ifstream file("users.txt");
        string u, p;
        if (file.is_open()) {
            while (file >> u >> p) {
                if (u == uname && p == pass) {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }
    static bool userExists(string uname) {
        ifstream file("users.txt");
        string u, p;
        if (file.is_open()) {
            while (file >> u >> p) {
                if (u == uname) {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        return false;
    }
    static string getPasswordForUser(string uname) {
        ifstream file("users.txt");
        string u, p;
        if (file.is_open()) {
            while (file >> u >> p) {
                if (u == uname) {
                    file.close();
                    return p;
                }
            }
            file.close();
        }
        return "";
    }
};
class AuthSystem {
public:
    void registerUser() {
        string uname, pass;
        cout << "\n=== User Registration ===\n";
        cout << "Enter username: ";
        cin >> uname;

        if (User::userExists(uname)) {
            cout << " Username already exists! Try a different one.\n";
            return;
        }

        cout << "Enter password: ";
        cin >> pass;

        User newUser(uname, pass);
        newUser.saveToFile();
        cout << " Registration successful!\n";
    }

    void loginUser() {
        string uname, pass;
        cout << "\n=== User Login ===\n";
        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pass;

        if (User::authenticate(uname, pass)) {
            cout << " Login successful! Welcome " << uname << endl;
        } else {
            cout << " Invalid username or password.\n";
        }
    }

    void verifyPassword() {
        string uname;
        cout << "\n Password Verification ===\n";
        cout << "Enter username: ";
        cin >> uname;

        if (!User::userExists(uname)) {
            cout << " User not found.\n";
            return;
        }

        string savedPass = User::getPasswordForUser(uname);
        cout << "Stored password for user " << uname << " is: " << savedPass << endl;
    }
};
int main() {
    AuthSystem system;
    int choice;

    do {
        cout << "\n Login & Registration System ===\n";
        cout << "1. Register\n2. Login\n3. Verify Password\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.registerUser(); break;
            case 2: system.loginUser(); break;
            case 3: system.verifyPassword(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
