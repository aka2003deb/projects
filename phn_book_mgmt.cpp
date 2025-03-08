#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <windows.h>

using namespace std;

#define MAX_LENGTH 255
#define ENTER 13
#define TAB 9
#define BKSP 8
#define USER_CODE 101
#define ADMIN_CODE 102

class Phonebook {
private:
    struct Record {
        string firstName;
        string lastName;
        char gender;
        string phoneNumber;
        string cityName;
    };

    string adminPassword = "Admin";
    string findNumber;
    Record contact;
    int choice = 0;

    bool isValidGender(char& gender);
    bool isValidNumeric(const string& num);
    bool isValidName(const string& name);
    bool checkNumberExistence(const string& num);
    string removeSpaces(string str);

    void clearScreen();
    void infoScreen();
    void loginPage();
    void adminLogin();
    void userPanel();
    void adminPanel();
    void addNewContact();
    void updateContact();
    void deleteContact();
    void deleteAllContact();
    void displayContact(int entryCode);
    void searchByName(int entryCode);
    void searchByNumber(int entryCode);
    void searchByCity(int entryCode);
    void endScreen();

public:
    Phonebook() {
        infoScreen(); // Starts with the introduction screen and moves on to the login page.
    }

    ~Phonebook() {
        // Destructor could perform cleanup tasks if needed.
    }
};

int main() {
    Phonebook pb; // Starts the application.
    return 0;
}

bool Phonebook::isValidGender(char& gender) {
    if (gender == 'M' || gender == 'm') {
        gender = 'm';
        return true;
    } else if (gender == 'F' || gender == 'f') {
        gender = 'f';
        return true;
    } else {
        cout << "ERROR: Invalid gender, try again later.\n";
        return false;
    }
}

bool Phonebook::isValidNumeric(const string& num) {
    if (num.length() != 10) {
        cout << "ERROR: Phone number must be of 10 digits.\n";
        return false;
    }
    for (char digit : num) {
        if (!isdigit(digit)) {
            cout << "ERROR: Phone number must contain only digits.\n";
            return false;
        }
    }
    return true;
}

bool Phonebook::isValidName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {
            cout << "ERROR: Invalid name, try again later.\n";
            return false;
        }
    }
    return true;
}

bool Phonebook::checkNumberExistence(const string& num) {
    ifstream inFile("ContactList.txt");
    Record rec;
    while (inFile >> rec.firstName >> rec.lastName >> rec.gender >> rec.phoneNumber >> rec.cityName) {
        if (rec.phoneNumber == num) {
            inFile.close();
            return false;
        }
    }
    inFile.close();
    return true;
}

string Phonebook::removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void Phonebook::clearScreen() {
    system("cls");
}

void Phonebook::infoScreen() {
    clearScreen();
    system("title Phonebook Management System");
    cout << "-------------------------------------------\n"
         << "   >>> Phonebook Management System <<<\n"
         << "-------------------------------------------\n\n"
         << "It is a software application that allows users to store, organize\n"
         << "and manage large numbers of contact records efficiently. The system is designed\n"
         << "to have functions such as adding, updating, viewing, and deleting contacts.\n\n"
         << "------------------------------------\n";
    system("pause");
    loginPage();
}

void Phonebook::loginPage() {
    clearScreen();
    cout << "-----------------------------------\n"
         << "   >>> Login into system as <<<\n"
         << "-----------------------------------\n"
         << "[1] Administrator.\n"
         << "[2] User profile.\n"
         << "[3] EXIT.\n"
         << "-----------------------------------\n\n"
         << "Enter the number & Hit ENTER: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            adminLogin();
            break;
        case 2:
            userPanel();
            break;
        case 3:
            endScreen();
            break;
        default:
            cout << "ERROR: Invalid input please try again.\n";
            system("pause");
            loginPage();
    }
}

void Phonebook::endScreen() {
    clearScreen();
    system("title Credits Page");
    cout << "------------------------------------------\n"
         << "   >>> Phonebook Management System <<<\n"
         << "------------------------------------------\n"
         << "Thank You.\n"
         << "------------------------------------------\n\n";
    Sleep(1500);
    exit(0);
}

void Phonebook::adminLogin() {
    clearScreen();
    system("title Admin Login");
    cout << "-----------------------------------\n"
         << "   >>> Administrator Login <<<\n"
         << "-----------------------------------\n\n"
         << "Enter your password & Hit ENTER: ";
    string inputPassword;
    cin >> inputPassword;

    if (inputPassword == adminPassword) {
        adminPanel();
    } else {
        cout << "ERROR: Invalid password please try again.\n";
        system("pause");
        loginPage();
    }
}

void Phonebook::userPanel() {
    clearScreen();
    system("title User Panel");
    cout << "-----------------------------------\n"
         << "\t>>> User Panel <<<\n"
         << "-----------------------------------\n"
         << "[1] Display All Contact.\n"
         << "[2] Search By Name.\n"
         << "[3] Search By Number.\n"
         << "[4] Search By City.\n"
         << "[5] Back to Login.\n"
         << "[6] EXIT.\n"
         << "-----------------------------------\n\n"
         << "Enter the number & Hit ENTER: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            displayContact(USER_CODE);
            break;
        case 2:
            searchByName(USER_CODE);
            break;
        case 3:
            searchByNumber(USER_CODE);
            break;
        case 4:
            searchByCity(USER_CODE);
            break;
        case 5:
            loginPage();
            break;
        case 6:
            endScreen();
            break;
        default:
            cout << "ERROR: Invalid input please try again.\n";
            system("pause");
            userPanel();
    }
}

void Phonebook::adminPanel() {
    clearScreen();
    system("title Admin Panel");
    cout << "------------------------------------\n"
         << "\t>>> Admin Panel <<<\n"
         << "------------------------------------\n"
         << " [1] Add New Contact.\n"
         << " [2] Update Contact.\n"
         << " [3] Display All Contact.\n"
         << " [4] Search By Name.\n"
         << " [5] Search By Number.\n"
         << " [6] Search By City.\n"
         << " [7] Delete Contact.\n"
         << " [8] Delete All Contact.\n"
         << " [9] Back to Login.\n"
         << "[10] EXIT.\n"
         << "------------------------------------\n\n"
         << "Enter the number & Hit ENTER: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            addNewContact();
            break;
        case 2:
            updateContact();
            break;
        case 3:
            displayContact(ADMIN_CODE);
            break;
        case 4:
            searchByName(ADMIN_CODE);
            break;
        case 5:
            searchByNumber(ADMIN_CODE);
            break;
        case 6:
            searchByCity(ADMIN_CODE);
            break;
        case 7:
            deleteContact();
            break;
        case 8:
            deleteAllContact();
            break;
        case 9:
            loginPage();
            break;
        case 10:
            endScreen();
            break;
        default:
            cout << "ERROR: Invalid input please try again.\n";
            system("pause");
            adminPanel();
    }
}

void Phonebook::addNewContact() {
    clearScreen();
    system("title Add New Contact");
    cout << "------------------------------\n"
         << "   >>> Add New Contact <<<\n"
         << "------------------------------\n\n";
    ofstream outFile("ContactList.txt", ios::app);

    cout << "Enter the first name: ";
    getline(cin, contact.firstName);
    cout << "Enter the last name: ";
    getline(cin, contact.lastName);
    cout << "Enter the city name: ";
    getline(cin, contact.cityName);
    cout << "Enter the gender [M/F]: ";
    cin >> contact.gender;
    cin.ignore();
    cout << "Enter the phone number [+91]: ";
    getline(cin, contact.phoneNumber);

    if (isValidGender(contact.gender) && isValidNumeric(contact.phoneNumber)) {
        if (checkNumberExistence(contact.phoneNumber)) {
            outFile << removeSpaces(contact.firstName) << " "
                    << removeSpaces(contact.lastName) << " "
                    << tolower(contact.gender) << " "
                    << contact.phoneNumber << " "
                    << removeSpaces(contact.cityName) << "\n";
            cout << "Success: Contact details added in the record.\n";
        } else {
            cout << "ERROR: Phone number already exists in the database.\n";
        }
    } else {
        cout << "ERROR: Invalid input for phone number or gender, try again later.\n";
    }
    outFile.close();
    system("pause");
    adminPanel();
}

void Phonebook::updateContact() {
    clearScreen();
    system("title Update Contact");
    cout << "-----------------------------\n"
         << "   >>> Update Contact <<<\n"
         << "-----------------------------\n\n"
         << "Enter the phone number to update [+91]: ";
    getline(cin, findNumber);

    if (!isValidNumeric(findNumber)) {
        adminPanel();
        return;
    }

    ifstream inFile("ContactList.txt");
    ofstream outFile("temporary.txt");
    bool found = false;

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        if (contact.phoneNumber == findNumber) {
            cout << "Contact Found: " << contact.firstName << " " << contact.lastName << " - " << contact.cityName << "\n";
            cout << "Enter new details:\n";
            cout << "First name: ";
            getline(cin, contact.firstName);
            cout << "Last name: ";
            getline(cin, contact.lastName);
            cout << "City name: ";
            getline(cin, contact.cityName);

            outFile << removeSpaces(contact.firstName) << " "
                    << removeSpaces(contact.lastName) << " "
                    << contact.gender << " "
                    << contact.phoneNumber << " "
                    << removeSpaces(contact.cityName) << "\n";
            found = true;
        } else {
            outFile << contact.firstName << " "
                    << contact.lastName << " "
                    << contact.gender << " "
                    << contact.phoneNumber << " "
                    << contact.cityName << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove("ContactList.txt");
    rename("temporary.txt", "ContactList.txt");

    if (found) {
        cout << "Contact updated successfully.\n";
    } else {
        cout << "No contact found with the provided phone number.\n";
    }

    system("pause");
    adminPanel();
}

void Phonebook::deleteContact() {
    clearScreen();
    system("title Delete Contact");
    cout << "-----------------------------\n"
         << "   >>> Delete Contact <<<\n"
         << "-----------------------------\n\n"
         << "Enter the phone number to delete [+91]: ";
    getline(cin, findNumber);

    if (!isValidNumeric(findNumber)) {
        adminPanel();
        return;
    }

    ifstream inFile("ContactList.txt");
    ofstream outFile("temporary.txt");
    bool found = false;

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        if (contact.phoneNumber == findNumber) {
            cout << "Deleting contact: " << contact.firstName << " " << contact.lastName << "\n";
            found = true;  // Contact will not be written to the temporary file.
        } else {
            outFile << contact.firstName << " "
                    << contact.lastName << " "
                    << contact.gender << " "
                    << contact.phoneNumber << " "
                    << contact.cityName << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove("ContactList.txt");
    rename("temporary.txt", "ContactList.txt");

    if (found) {
        cout << "Contact deleted successfully.\n";
    } else {
        cout << "No contact found with the provided phone number.\n";
    }

    system("pause");
    adminPanel();
}

void Phonebook::deleteAllContact() {
    clearScreen();
    system("title Delete All Contact");
    cout << "---------------------------------\n"
         << "   >>> Delete All Contact <<<\n"
         << "---------------------------------\n\n"
         << "Type CONFIRM to delete all contacts: ";
    string confirmation;
    getline(cin, confirmation);

    if (confirmation == "CONFIRM") {
        ofstream outFile("ContactList.txt", ios::trunc);  // Truncate the file to zero length.
        outFile.close();
        cout << "All contacts deleted successfully.\n";
    } else {
        cout << "ERROR: Invalid confirmation message.\n";
    }

    system("pause");
    adminPanel();
}

void Phonebook::displayContact(int entryCode) {
    clearScreen();
    system("title Display All Contact");
    ifstream inFile("ContactList.txt");
    int count = 1;
    bool found = false;

    cout << "\n>>> Contacts List <<<\n\n";
    cout << left << setw(5) << "ID" << "|"
         << left << setw(20) << " Name" << "|"
         << left << setw(8) << " Gender" << "|"
         << left << setw(15) << " Phone Number" << "|"
         << left << setw(20) << " City Name" << "|\n";
    cout << setfill('-') << setw(74) << "-" << setfill(' ') << "\n";

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        if (!found) {
            found = true;
        }
        cout << left << setw(5) << count++ << "|"
             << left << setw(20) << contact.firstName + " " + contact.lastName << "|"
             << left << setw(8) << " " + string(1, contact.gender) << "|"
             << left << setw(15) << " " + contact.phoneNumber << "|"
             << left << setw(20) << " " + contact.cityName << "|\n";
    }

    if (!found) {
        cout << "No contacts found.\n";
    }

    inFile.close();
    system("pause");
    entryCode == USER_CODE ? userPanel() : adminPanel();
}

void Phonebook::searchByName(int entryCode) {
    clearScreen();
    system("title Search By Name");
    cout << "-----------------------------\n"
         << "   >>> Search By Name <<<\n"
         << "-----------------------------\n\n"
         << "Enter the name to search: ";
    string name;
    getline(cin, name);
    name = removeSpaces(name);
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    ifstream inFile("ContactList.txt");
    int count = 1;
    bool found = false;

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        string firstNameLower = contact.firstName;
        string lastNameLower = contact.lastName;
        transform(firstNameLower.begin(), firstNameLower.end(), firstNameLower.begin(), ::tolower);
        transform(lastNameLower.begin(), lastNameLower.end(), lastNameLower.begin(), ::tolower);

        if (firstNameLower.find(name) != string::npos || lastNameLower.find(name) != string::npos) {
            if (!found) {
                cout << "| ID | Name          | Gender | Phone Number | City Name |\n"
                     << "----------------------------------------------------------\n";
                found = true;
            }
            cout << "| " << count++ << " | " << contact.firstName << " " << contact.lastName
                 << " | " << contact.gender << " | " << contact.phoneNumber << " | " << contact.cityName << " |\n";
        }
    }

    if (!found) {
        cout << "No contacts found with the provided name.\n";
    }

    inFile.close();
    system("pause");
    entryCode == USER_CODE ? userPanel() : adminPanel();
}

void Phonebook::searchByNumber(int entryCode) {
    clearScreen();
    system("title Search By Number");
    cout << "-------------------------------\n"
         << "   >>> Search By Number <<<\n"
         << "-------------------------------\n\n"
         << "Enter the phone number to search: ";
    getline(cin, findNumber);

    if (!isValidNumeric(findNumber)) {
        entryCode == USER_CODE ? userPanel() : adminPanel();
        return;
    }

    ifstream inFile("ContactList.txt");
    int count = 1;
    bool found = false;

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        if (contact.phoneNumber == findNumber) {
            if (!found) {
                cout << "| ID | Name          | Gender | Phone Number | City Name |\n"
                     << "----------------------------------------------------------\n";
                found = true;
            }
            cout << "| " << count++ << " | " << contact.firstName << " " << contact.lastName
                 << " | " << contact.gender << " | " << contact.phoneNumber << " | " << contact.cityName << " |\n";
        }
    }

    if (!found) {
        cout << "No contacts found with the provided phone number.\n";
    }

    inFile.close();
    system("pause");
    entryCode == USER_CODE ? userPanel() : adminPanel();
}

void Phonebook::searchByCity(int entryCode) {
    clearScreen();
    system("title Search By City Name");
    cout << "-----------------------------\n"
         << "   >>> Search By City <<<\n"
         << "-----------------------------\n\n"
         << "Enter the city name to search: ";
    string city;
    getline(cin, city);
    city = removeSpaces(city);
    transform(city.begin(), city.end(), city.begin(), ::tolower);

    ifstream inFile("ContactList.txt");
    int count = 1;
    bool found = false;

    while (inFile >> contact.firstName >> contact.lastName >> contact.gender >> contact.phoneNumber >> contact.cityName) {
        string cityNameLower = contact.cityName;
        transform(cityNameLower.begin(), cityNameLower.end(), cityNameLower.begin(), ::tolower);
        if (cityNameLower.find(city) != string::npos) {
            if (!found) {
                cout << "| ID | Name          | Gender | Phone Number | City Name |\n"
                     << "----------------------------------------------------------\n";
                found = true;
            }
            cout << "| " << count++ << " | " << contact.firstName << " " << contact.lastName
                 << " | " << contact.gender << " | " << contact.phoneNumber << " | " << cityNameLower << " |\n";
        }
    }

    if (!found) {
        cout << "No contacts found in the provided city.\n";
    }

    inFile.close();
    system("pause");
    entryCode == USER_CODE ? userPanel() : adminPanel();
}
