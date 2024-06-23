#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string phoneNo, name, address, description, search;
    fstream file;

public:
    void addContact();
    void showAll();
    void searchContact();
    void deleteContact();
} obj;

int main()
{
    char choice;

    while (true)
    {
        cout << "1 --> Add Contact " << endl;
        cout << "2 --> Show All Contact " << endl;
        cout << "3 --> Search Contact " << endl;
        cout << "4 --> Delete Contact " << endl;
        cout << "0 --> Exit " << endl;
        cin >> choice;

        switch (choice)
        {
        case '1':
            obj.addContact();
            break;
        case '2':
            obj.showAll();
            break;
        case '3':
            obj.searchContact();
            break;
        case '4':
            obj.deleteContact();
            break;
        case '0':
            return 0;
        default:
            cout << "Invalid Selection ...!" << endl;
            break;
        }
    }

    return 0;
}

void temp::addContact()
{
    cout << "Enter phone Number :: ";
    cin >> phoneNo;
    cout << "Enter Name :: ";
    cin >> name;
    cout << "Enter Address :: ";
    cin >> address;
    cout << "Enter Description :: ";
    cin >> description;

    file.open("data.csv", ios::out | ios::app); // output and append mode
    file << phoneNo << "," << name << "," << address << "," << description << "\n";
    file.close();
}

void temp::showAll()
{
    file.open("data.csv", ios::in);

    if (!file.is_open())
    {
        cout << "No contacts to show." << endl;
        return;
    }

    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description, '\n'))
    {
        cout << "Phone Number :: " << phoneNo << endl;
        cout << "Name :: " << name << endl;
        cout << "Address :: " << address << endl;
        cout << "Description :: " << description << endl
             << endl;
    }
    file.close();
}

void temp::searchContact()
{
    cout << "Enter Phone Number :: ";
    cin.ignore();
    getline(cin, search);

    file.open("data.csv", ios::in); // open file in read mode

    if (!file.is_open())
    {
        cout << "No contacts found." << endl;
        return;
    }

    bool found = false;
    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description, '\n'))
    {
        if (phoneNo == search)
        {
            cout << "Phone Number :: " << phoneNo << endl;
            cout << "Name :: " << name << endl;
            cout << "Address :: " << address << endl;
            cout << "Description :: " << description << endl
                 << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Contact not found." << endl;
    }
    file.close();
}

void temp::deleteContact()
{
    cout << "Enter Phone Number to delete :: ";
    cin.ignore();
    getline(cin, search);

    file.open("data.csv", ios::in);
    if (!file.is_open())
    {
        cout << "No contacts found." << endl;
        return;
    }

    vector<string> lines;
    bool found = false;
    while (getline(file, phoneNo, ',') &&
           getline(file, name, ',') &&
           getline(file, address, ',') &&
           getline(file, description, '\n'))
    {
        if (phoneNo == search)
        {
            found = true;
            continue;
        }
        lines.push_back(phoneNo + "," + name + "," + address + "," + description);
    }
    file.close();

    if (found)
    {
        file.open("data.csv", ios::out | ios::trunc); // truncate mode
        for (const auto &line : lines)
        {
            file << line << "\n";
        }
        file.close();
        cout << "Contact deleted successfully." << endl;
    }
    else
    {
        cout << "Contact not found." << endl;
    }
}
