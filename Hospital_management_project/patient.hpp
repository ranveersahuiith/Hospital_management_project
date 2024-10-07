#include <bits/stdc++.h>
using namespace std;

class PATIENT
{
public:
    string UID;
    string name;
    string department;
    string patientType;
    string rollNum;
    string contact;
    string mail;
    string rating;
    string address;
    string history;
};

class Patients_Directory
{
public:
    unordered_map<string, PATIENT> patientsDataByUID;
    multimap<string, PATIENT> patientsDataByName;
    multimap<string, PATIENT> patientsDataByDepartment;
    multimap<string, PATIENT> patientsDataByPatientType;
    unordered_map<string, PATIENT> patientsDataByRollNum;
    multimap<string, PATIENT> patientsDataByContact;
    multimap<string, PATIENT> patientsDataByMail;
    multimap<double, PATIENT> patientsDataByRating;

    void enterPatientDatabase();
    void getPatientList();
    void insertPatient();
    void deletePatient();
    void editPatient();
    void searchPatient();
};

void Patients_Directory ::enterPatientDatabase()
{
    cout << endl;
    cout << "WELCOME TO THE DIRECTORY OF PATIENTS " << endl;
    cout << "PLEASE ENTER YOUR CHOICE " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. GET THE LIST OF ALL THE PATIENTS " << endl;
    cout << "2. REGISTER NEWLY APPOINTED PATIENT " << endl;
    cout << "3. DEREGISTER PATIENT " << endl;
    cout << "4. EDIT THE DETAIL OF PATIENT " << endl;
    cout << "5. SEARCH ANY PATIENT IN THE DIRECTORY" << endl;
    cout << "6. EXIT" << endl;
    cout << "------------------------------------------------" << endl
         << endl;
    cout << "Enter your choice: ";

    string str_choice;
    getline(cin, str_choice);
    int choice = stoi(str_choice);

    switch (choice)
    {
    case 1:
    {
        getPatientList();
        break;
    }
    case 2:
    {
        insertPatient();
        break;
    }
    case 3:
    {
        deletePatient();
        break;
    }
    case 4:
    {
        editPatient();
        break;
    }
    case 5:
    {
        searchPatient();
        break;
    }
    case 6:
    {
        break;
    }
    default:
    {
        cout << "Not a valid choice. Please Enter a valid choice." << endl;
        break;
    }
    }
}

void Patients_Directory ::getPatientList()
{
    fstream myFile;
    myFile.open("PatientsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            PATIENT temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.patientType, ',');
            getline(myFile, temp.rollNum, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.address, ',');
            getline(myFile, temp.history);
            patientsDataByName.insert({temp.name, temp});
        }
        cout << endl;
        cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
        for (auto itr = patientsDataByName.begin(); itr != patientsDataByName.end(); itr++)
        {
            cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                 << '\n';
        }
        cout << endl;
    }
    else
    {
        cout << "Directory is Empty." << endl;
    }
}

void Patients_Directory ::insertPatient()
{
    fstream myFile;
    myFile.open("PatientsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            PATIENT temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.patientType, ',');
            getline(myFile, temp.rollNum, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.address, ',');
            getline(myFile, temp.history);
            patientsDataByUID.insert({temp.UID, temp});
        }
    }

    PATIENT temp;
    cout << "Enter the ID Card Number of the Patient" << endl;
    getline(cin, temp.UID);
    if (auto it = patientsDataByUID.find(temp.UID) != patientsDataByUID.end())
    {
        cout << "PATIENT WITH THIS UID ALREADY EXISTS\n";
        return;
    }
    cout << "Enter the Name of the Patient" << endl;
    getline(cin, temp.name);
    cout << "Enter the Department of the Patient" << endl;
    getline(cin, temp.department);
    cout << "Enter the Patient Type of the Patient" << endl;
    getline(cin, temp.patientType);
    cout << "Enter the Roll Number of the Patient" << endl;
    getline(cin, temp.rollNum);
    cout << "Enter the Contact Number of the Patient" << endl;
    getline(cin, temp.contact);
    cout << "Enter the Email ID of the Patient" << endl;
    getline(cin, temp.mail);
    temp.rating = '0';
    cout << "Enter the Address of the Patient" << endl;
    getline(cin, temp.address);
    temp.history = '-';

    patientsDataByUID.insert({temp.UID, temp});

    fstream myNewFile;
    myNewFile.open("PatientsDataNew.csv", ios::out);

    for (auto itr = patientsDataByUID.begin(); itr != patientsDataByUID.end(); itr++)
    {
        myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.patientType << ',' << itr->second.rollNum << ',' << itr->second.contact << ',' << itr->second.mail << ',' << itr->second.rating << ',' << itr->second.address << ',' << itr->second.history;
        if (next(itr) != patientsDataByUID.end())
            myNewFile << "\n";
    }

    myFile.close();
    myNewFile.close();

    remove("PatientsData.csv");
    rename("PatientsDataNew.csv", "PatientsData.csv");
}

void Patients_Directory ::deletePatient()
{
    fstream myFile;
    myFile.open("PatientsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            PATIENT temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.patientType, ',');
            getline(myFile, temp.rollNum, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.address, ',');
            getline(myFile, temp.history);
            patientsDataByUID.insert({temp.UID, temp});
        }
    }

    string temp;
    cout << "Enter the UID of the Patient to be deleted.\n";
    getline(cin, temp);
    patientsDataByUID.erase(temp);

    fstream myNewFile;
    myNewFile.open("PatientsDataNew.csv", ios::out);

    for (auto itr = patientsDataByUID.begin(); itr != patientsDataByUID.end(); itr++)
    {
        myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.patientType << ',' << itr->second.rollNum << ',' << itr->second.contact << ',' << itr->second.mail << ',' << itr->second.rating << ',' << itr->second.address << ',' << itr->second.history;
        if (next(itr) != patientsDataByUID.end())
            myNewFile << "\n";
    }

    myFile.close();
    myNewFile.close();

    remove("PatientsData.csv");
    rename("PatientsDataNew.csv", "PatientsData.csv");
}

void Patients_Directory ::editPatient()
{
    fstream myFile;
    myFile.open("PatientsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            PATIENT temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.patientType, ',');
            getline(myFile, temp.rollNum, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.address, ',');
            getline(myFile, temp.history);
            patientsDataByUID.insert({temp.UID, temp});
        }
    }
    cout << "Enter the UID of the Patient you want to edit.\n";
    string temp;
    getline(cin, temp);
    auto it = patientsDataByUID.find(temp);
    if (it != patientsDataByUID.end())
    {
        cout << "PLEASE ENTER YOUR CHOICE WHAT YOU WANT TO EDIT" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "1. NAME" << endl;
        cout << "2. DEPARTMENT" << endl;
        cout << "3. PATIENT TYPE" << endl;
        cout << "4. ROLL NUMBER" << endl;
        cout << "5. ADDRESS" << endl;
        cout << "6. CONTACT" << endl;
        cout << "7. EMAIL" << endl;
        cout << "------------------------------------------------" << endl
             << endl;
        cout << "Enter your choice: ";

        string str_choice;
        getline(cin, str_choice);
        int choice = stoi(str_choice);

        switch (choice)
        {
        case 1:
        {
            cout << "Enter New Name of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.name = temp1;
            break;
        }
        case 2:
        {
            cout << "Enter New Department of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.department = temp1;
            break;
        }
        case 3:
        {
            cout << "Enter New PATIENT TYPE of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.patientType = temp1;
            break;
        }
        case 4:
        {
            cout << "Enter New Roll Number of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.rollNum = temp1;
            break;
        }
        case 5:
        {
            cout << "Enter New Address of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.address = temp1;
            break;
        }
        case 6:
        {
            cout << "Enter New Contact of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.contact = temp1;
            break;
        }
        case 7:
        {
            cout << "Enter New Mail of the Patient" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.mail = temp1;
            break;
        }
        default:
        {
            cout << "Not a valid choice. Please Enter a valid choice." << endl;
            break;
        }
        }
        fstream myNewFile;
        myNewFile.open("PatientsDataNew.csv", ios::out);

        for (auto itr = patientsDataByUID.begin(); itr != patientsDataByUID.end(); itr++)
        {
            myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.patientType << ',' << itr->second.rollNum << ',' << itr->second.contact << ',' << itr->second.mail << ',' << itr->second.rating << ',' << itr->second.address << ',' << itr->second.history;
            if (next(itr) != patientsDataByUID.end())
                myNewFile << "\n";
        }

        myFile.close();
        myNewFile.close();

        remove("PatientsData.csv");
        rename("PatientsDataNew.csv", "PatientsData.csv");
    }
    else
    {
        cout << "Patient Not Found." << endl;
        myFile.close();
    }
}

void Patients_Directory ::searchPatient()
{
    cout << "PLEASE ENTER FROM WHAT DETAILS YOU WANT TO SEARCH" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. UID" << endl;
    cout << "2. NAME" << endl;
    cout << "3. DEPARTMENT" << endl;
    cout << "4. PATIENT TYPE" << endl;
    cout << "5. ROLL NUMBER" << endl;
    cout << "6. CONTACT" << endl;
    cout << "7. EMAIL" << endl;
    cout << "------------------------------------------------" << endl
         << endl;
    cout << "Enter your choice: ";

    string str_choice;
    getline(cin, str_choice);
    int choice = stoi(str_choice);

    switch (choice)
    {
    case 1:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByUID.insert({temp.UID, temp});
            }
        }
        cout << "Enter the UID of the Patient: ";
        string temp1;
        getline(cin, temp1);
        auto itr = patientsDataByUID.find(temp1);

        if (itr != patientsDataByUID.end())
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                 << '\n';
            myFile.close();
        }
        else
        {
            cout << "Patient Not Found." << endl;
            myFile.close();
        }
        break;
    }
    case 2:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByName.insert({temp.name, temp});
            }
        }
        cout << "Enter the Name of the Patient: ";
        string temp1;
        getline(cin, temp1);
        int a = patientsDataByName.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            auto it = patientsDataByName.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO STAFF WITH GIVEN NAME." << endl;
            myFile.close();
        }
        break;
    }
    case 3:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByDepartment.insert({temp.department, temp});
            }
        }
        cout << "Enter the Department of the Patient: ";
        string temp1;
        getline(cin, temp1);
        int a = patientsDataByDepartment.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            auto it = patientsDataByDepartment.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO ANY STAFF IN THIS DEPARTMENT" << endl;
            myFile.close();
        }
        break;
    }
    case 4:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByPatientType.insert({temp.patientType, temp});
            }
        }
        cout << "Enter the Patient Type of the Patient: ";
        string temp1;
        getline(cin, temp1);
        int a = patientsDataByPatientType.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            auto it = patientsDataByPatientType.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO ANY STAFF WITH THIS PATIENT TYPE" << endl;
            myFile.close();
        }
        break;
    }
    case 5:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByRollNum.insert({temp.rollNum, temp});
            }
        }
        cout << "Enter the Roll Number of the Patient: ";
        string temp1;
        getline(cin, temp1);
        auto itr = patientsDataByRollNum.find(temp1);

        if (itr != patientsDataByRollNum.end())
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                 << '\n';
            myFile.close();
        }
        else
        {
            cout << "Patient Not Found." << endl;
            myFile.close();
        }
        break;
    }
    case 6:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                patientsDataByContact.insert({temp.contact, temp});
            }
        }
        cout << "Enter the Contact of the Patient: ";
        string temp1;
        getline(cin, temp1);
        int a = patientsDataByContact.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            auto it = patientsDataByContact.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO ANY STAFF WITH THIS CONTACT." << endl;
            myFile.close();
        }
        break;
    }
    case 7:
    {
        fstream myFile;
        myFile.open("PatientsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                PATIENT temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.patientType, ',');
                getline(myFile, temp.rollNum, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.address, ',');
                getline(myFile, temp.history);
                ;
                patientsDataByMail.insert({temp.mail, temp});
            }
        }
        cout << "Enter the Email of the Patient: ";
        string temp1;
        getline(cin, temp1);
        int a = patientsDataByMail.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "ROLL" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "MAIL" << '\t' << '\t' << "RATING" << '\t' << '\t' << "ADDRESS" << '\t' << '\t' << "HISTORY"
             << '\n';
            auto it = patientsDataByMail.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << itr->second.department << '\t' << itr->second.patientType << '\t' << itr->second.rollNum << '\t' << itr->second.contact << '\t' << itr->second.mail << '\t' << itr->second.rating << '\t' << itr->second.address << '\t' << itr->second.history
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO ANY STAFF WITH THIS MAIL" << endl;
            myFile.close();
        }
        break;
    }
    default:
    {
        cout << "Not a valid choice. Please Enter a valid choice." << endl;
        break;
    }
    }
}