#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void registerUser() {
    string username, password, passwordConfirm;
    
    cout << "\n=== Registration ===\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Confirm password: ";
    getline(cin, passwordConfirm);
    
    if (password != passwordConfirm) {
        cout << "Passwords don't match. Try again.\n";
        return;
    }
    
    // Check if the username already exists
    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string fileUsername = line.substr(0, pos);
            if (fileUsername == username) {
                cout << "Username already exists. Please choose a different username.\n";
                return;
            }
        }
    }
    infile.close();

    // Append the new user to the file
    ofstream outfile("users.txt", ios::app);
    if (!outfile) {
        cout << "Error opening file for writing!\n";
        return;
    }
    outfile << username << ";" << password << "\n";
    outfile.close();
    
    cout << "Registration successful! Now you can login.\n";
}

void loginUser() {
    string username, password;
    
    cout << "\n=== Login ===\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    
    ifstream infile("users.txt");
    if (!infile) {
        cout << "No users found. Please register first.\n";
        return;
    }
    
    bool authenticated = false;
    string line;
    while (getline(infile, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string fileUsername = line.substr(0, pos);
            string filePassword = line.substr(pos + 1);
            // Remove potential newline characters from the filePassword
            if (!filePassword.empty() && filePassword.back() == '\r')
                filePassword.pop_back();
            if (fileUsername == username && filePassword == password) {
                authenticated = true;
                break;
            }
        }
    }
    infile.close();
    
    if (authenticated) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Invalid credentials. Please try again.\n";
    }
}

int main() {
    string choice;
    
    while (true) {
        cout << "\n====== Welcome to the Registration and Login CLI ======\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        getline(cin, choice);
        
        if (choice == "1") {
            registerUser();
        } else if (choice == "2") {
            loginUser();
        } else if (choice == "3") {
            cout << "Exiting... Catch you later!\n";
            break;
        } else {
            cout << "Invalid choice, try again!\n";
        }
    }
    
    return 0;
}
