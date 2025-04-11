// This program is a simple CLI-based student management system that allows adding, viewing, and searching for student records.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StudentManager
{
    string rollNum, name, fName, address;
    fstream file;

public:
    void addStu();
    void viewStu();
    void searchStu();
};

int main()
{
    char choice;
    StudentManager obj;

    cout << "-----------------------\n";
    cout << "1 - Add Student Record\n";
    cout << "2 - View All Student Records\n";
    cout << "3 - Search Student Record\n";
    cout << "4 - Exit\n";
    cout << "-----------------------\n";

    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // clear leftover newline

    switch (choice)
    {
    case '1':
        obj.addStu();
        break;
    case '2':
        obj.viewStu();
        break;
    case '3':
        obj.searchStu();
        break;
    case '4':
        return 0;
    default:
        cout << "Invalid choice...!\n";
        break;
    }
    return 0;
}

void StudentManager::addStu()
{
    cout << "Enter Student Roll Number: ";
    getline(cin, rollNum);
    cout << "Enter Student's Name: ";
    getline(cin, name);
    cout << "Enter Student Father's Name: ";
    getline(cin, fName);
    cout << "Enter Student Address: ";
    getline(cin, address);

    file.open("stuData.txt", ios::out | ios::app);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    file << rollNum << "*" << name << "*" << fName << "*" << address << "\n";
    file.close();
}

void StudentManager::viewStu()
{
    file.open("stuData.txt", ios::in);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    // Read each record using '*' as the delimiter.
    while (getline(file, rollNum, '*'))
    {
        getline(file, name, '*');
        getline(file, fName, '*');
        getline(file, address, '\n');
        cout << "\nStudent Roll Number: " << rollNum << "\n";
        cout << "Student's Name: " << name << "\n";
        cout << "Student Father's Name: " << fName << "\n";
        cout << "Student Address: " << address << "\n";
    }
    file.close();
}

void StudentManager::searchStu()
{
    cout << "Enter Student Roll Number to search: ";
    string key;
    getline(cin, key);
    bool found = false;

    file.open("stuData.txt", ios::in);
    if (!file)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    while (getline(file, rollNum, '*'))
    {
        getline(file, name, '*');
        getline(file, fName, '*');
        getline(file, address, '\n');
        if (rollNum == key)
        {
            cout << "\nRecord Found:\n";
            cout << "Student Roll Number: " << rollNum << "\n";
            cout << "Student's Name: " << name << "\n";
            cout << "Student Father's Name: " << fName << "\n";
            cout << "Student Address: " << address << "\n";
            found = true;
            break; // Exit after finding the match
        }
    }
    if (!found)
        cout << "No record found with roll number " << key << "\n";
    file.close();
}