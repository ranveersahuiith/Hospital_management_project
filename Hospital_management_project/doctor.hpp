// #ifndef Doctor_registry
// #define Doctor_registry

#include <bits/stdc++.h>
using namespace std;

class DOCTOR
{
public:
    string UID;
    string name;
    string department;
    string employType;
    string start;
    string end;
    string rating;
    string patCount;
    string contact;
    string mail;
};

class Doctors_Directory
{
public:
    unordered_map<string, DOCTOR> doctorsDataByUID;
    multimap<string, DOCTOR> doctorsDataByName;
    multimap<string, DOCTOR> doctorsDataByDepartment;
    multimap<string, DOCTOR> doctorsDataByStaff;
    multimap<string, DOCTOR> doctorsDataByContact;
    multimap<string, DOCTOR> doctorsDataByEmail;

    void enterDoctorDatabase();
    void getDoctorList();
    void insertDoctor();
    void deleteDoctor();
    void editDoctor();
    void searchDoctor();
};

void Doctors_Directory ::enterDoctorDatabase()
{
    cout << endl;
    cout << "WELCOME TO THE DIRECTORY OF DOCTORS " << endl;
    cout << "PLEASE ENTER YOUR CHOICE " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. GET THE LIST OF ALL THE DOCTORS " << endl;
    cout << "2. REGISTER NEWLY APPOINTED DOCTOR " << endl;
    cout << "3. DEREGISTER DOCTOR " << endl;
    cout << "4. EDIT THE DETAIL OF DOCTOR " << endl;
    cout << "5. SEARCH ANY DOCTOR IN THE DIRECTORY" << endl;
    cout << "6. QUIT THE PROGRAM" << endl;
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
        getDoctorList();
        break;
    }
    case 2:
    {
        insertDoctor();
        break;
    }
    case 3:
    {
        deleteDoctor();
        break;
    }
    case 4:
    {
        editDoctor();
        break;
    }
    case 5:
    {
        searchDoctor();
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

void Doctors_Directory ::getDoctorList()
{
    fstream myFile;
    myFile.open("DoctorsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            DOCTOR temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.employType, ',');
            getline(myFile, temp.start, ',');
            getline(myFile, temp.end, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.patCount, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail);
            doctorsDataByName.insert({temp.name, temp});
        }
        cout << endl;
        cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
             << '\n';
        for (auto itr = doctorsDataByName.begin(); itr != doctorsDataByName.end(); itr++)
        {
            cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
                 << '\n';
        }
        cout << endl;
    }
    else
    {
        cout << "Directory is Empty." << endl;
    }
}

void Doctors_Directory ::insertDoctor()
{
    fstream myFile;
    myFile.open("DoctorsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            DOCTOR temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.employType, ',');
            getline(myFile, temp.start, ',');
            getline(myFile, temp.end, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.patCount, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail);
            doctorsDataByUID.insert({temp.UID, temp});
        }
    }

    DOCTOR temp;
    cout << "Enter the ID Card Number of the Doctor" << endl;
    getline(cin, temp.UID);
    if (auto it = doctorsDataByUID.find(temp.UID) != doctorsDataByUID.end())
    {
        cout << "STAFF WITH THIS UID ALREADY EXISTS\n";
        return;
    }
    cout << "Enter the Name of the Doctor" << endl;
    getline(cin, temp.name);
    cout << "Enter the Department of the Doctor" << endl;
    getline(cin, temp.department);
    cout << "Enter the Staff Type of the Doctor" << endl;
    getline(cin, temp.employType);
    cout << "Enter the Start Time of the Doctor" << endl;
    getline(cin, temp.start);
    cout << "Enter the End Time of the Doctor" << endl;
    getline(cin, temp.end);
    temp.rating = '0';
    temp.patCount = '0';
    cout << "Enter the Contact Number of the Doctor" << endl;
    getline(cin, temp.contact);
    cout << "Enter the Email ID of the Doctor" << endl;
    getline(cin, temp.mail);

    doctorsDataByUID.insert({temp.UID, temp});

    fstream myNewFile;
    myNewFile.open("DoctorsDataNew.csv", ios::out);

    for (auto itr = doctorsDataByUID.begin(); itr != doctorsDataByUID.end(); itr++)
    {
        myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.employType << ',' << itr->second.start << ',' << itr->second.end << ',' << itr->second.rating << ',' << itr->second.patCount << ',' << itr->second.contact << ',' << itr->second.mail;
        if (next(itr) != doctorsDataByUID.end())
            myNewFile << "\n";
    }

    myFile.close();
    myNewFile.close();

    remove("DoctorsData.csv");
    rename("DoctorsDataNew.csv", "DoctorsData.csv");
}

void Doctors_Directory ::deleteDoctor()
{
    fstream myFile;
    myFile.open("DoctorsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            DOCTOR temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.employType, ',');
            getline(myFile, temp.start, ',');
            getline(myFile, temp.end, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.patCount, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail);
            doctorsDataByUID.insert({temp.UID, temp});
        }
    }

    string temp;
    cout << "Enter the UID of the Doctor to be deleted.\n";
    getline(cin, temp);
    doctorsDataByUID.erase(temp);

    fstream myNewFile;
    myNewFile.open("DoctorsDataNew.csv", ios::out);

    for (auto itr = doctorsDataByUID.begin(); itr != doctorsDataByUID.end(); itr++)
    {
        myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.employType << ',' << itr->second.start << ',' << itr->second.end << ',' << itr->second.rating << ',' << itr->second.patCount << ',' << itr->second.contact << ',' << itr->second.mail;
        if (next(itr) != doctorsDataByUID.end())
            myNewFile << "\n";
    }

    myFile.close();
    myNewFile.close();

    remove("DoctorsData.csv");
    rename("DoctorsDataNew.csv", "DoctorsData.csv");
}

void Doctors_Directory ::editDoctor()
{
    fstream myFile;
    myFile.open("DoctorsData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            DOCTOR temp;
            getline(myFile, temp.UID, ',');
            getline(myFile, temp.name, ',');
            getline(myFile, temp.department, ',');
            getline(myFile, temp.employType, ',');
            getline(myFile, temp.start, ',');
            getline(myFile, temp.end, ',');
            getline(myFile, temp.rating, ',');
            getline(myFile, temp.patCount, ',');
            getline(myFile, temp.contact, ',');
            getline(myFile, temp.mail);
            doctorsDataByUID.insert({temp.UID, temp});
        }
    }
    cout << "Enter the UID of the Doctor you want to edit.\n";
    string temp;
    getline(cin, temp);
    auto it = doctorsDataByUID.find(temp);
    if (it != doctorsDataByUID.end())
    {
        cout << "PLEASE ENTER YOUR CHOICE WHAT YOU WANT TO EDIT" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "1. NAME" << endl;
        cout << "2. DEPARTMENT" << endl;
        cout << "3. DESIGNATION" << endl;
        cout << "4. START TIME" << endl;
        cout << "5. END TIME" << endl;
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
            cout << "Enter New Name of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.name = temp1;
            break;
        }
        case 2:
        {
            cout << "Enter New Department of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.department = temp1;
            break;
        }
        case 3:
        {
            cout << "Enter New Designation of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.employType = temp1;
            break;
        }
        case 4:
        {
            cout << "Enter New Start Time of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.start = temp1;
            break;
        }
        case 5:
        {
            cout << "Enter New End Time of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.end = temp1;
            break;
        }
        case 6:
        {
            cout << "Enter New Contact of the Doctor" << endl;
            string temp1;
            getline(cin, temp1);
            it->second.contact = temp1;
            break;
        }
        case 7:
        {
            cout << "Enter New Mail of the Doctor" << endl;
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
        myNewFile.open("DoctorsDataNew.csv", ios::out);

        for (auto itr = doctorsDataByUID.begin(); itr != doctorsDataByUID.end(); itr++)
        {
            myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.employType << ',' << itr->second.start << ',' << itr->second.end << ',' << itr->second.rating << ',' << itr->second.patCount << ',' << itr->second.contact << ',' << itr->second.mail;
            if (next(itr) != doctorsDataByUID.end())
                myNewFile << "\n";
        }

        myFile.close();
        myNewFile.close();

        remove("DoctorsData.csv");
        rename("DoctorsDataNew.csv", "DoctorsData.csv");
    }
    else
    {
        cout << "Staff Not Found." << endl;
        myFile.close();
    }
}

void Doctors_Directory ::searchDoctor()
{
    cout << "PLEASE ENTER FROM WHAT DETAILS YOU WANT TO SEARCH" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. UID" << endl;
    cout << "2. NAME" << endl;
    cout << "3. DEPARTMENT" << endl;
    cout << "4. DESIGNATION" << endl;
    cout << "5. CONTACT" << endl;
    cout << "6. EMAIL" << endl;
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
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByUID.insert({temp.UID, temp});
            }
        }
        cout << "Enter the UID of the Doctor: ";
        string temp1;
        getline(cin, temp1);
        auto itr = doctorsDataByUID.find(temp1);

        if (itr != doctorsDataByUID.end())
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
                 << '\n';
            myFile.close();
        }
        else
        {
            cout << "Staff Not Found." << endl;
            myFile.close();
        }
        break;
    }
    case 2:
    {
        fstream myFile;
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByName.insert({temp.name, temp});
            }
        }
        cout << "Enter the Name of the Doctor: ";
        string temp1;
        getline(cin, temp1);
        int a = doctorsDataByName.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doctorsDataByName.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
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
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByDepartment.insert({temp.department, temp});
            }
        }
        cout << "Enter the Department of the Doctor: ";
        string temp1;
        getline(cin, temp1);
        int a = doctorsDataByDepartment.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doctorsDataByDepartment.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
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
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByStaff.insert({temp.employType, temp});
            }
        }
        cout << "Enter the Designation of the Staff: ";
        string temp1;
        getline(cin, temp1);
        int a = doctorsDataByStaff.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doctorsDataByStaff.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
                     << '\n';
            }
            myFile.close();
        }
        else
        {
            cout << "NO ANY STAFF WITH THIS DESIGNATION" << endl;
            myFile.close();
        }
        break;
    }
    case 5:
    {
        fstream myFile;
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByContact.insert({temp.contact, temp});
            }
        }
        cout << "Enter the Contact of the Staff: ";
        string temp1;
        getline(cin, temp1);
        int a = doctorsDataByContact.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doctorsDataByContact.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
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
    case 6:
    {
        fstream myFile;
        myFile.open("DoctorsData.csv", ios::in);
        if (myFile.peek() != EOF)
        {
            while (!myFile.eof())
            {
                DOCTOR temp;
                getline(myFile, temp.UID, ',');
                getline(myFile, temp.name, ',');
                getline(myFile, temp.department, ',');
                getline(myFile, temp.employType, ',');
                getline(myFile, temp.start, ',');
                getline(myFile, temp.end, ',');
                getline(myFile, temp.rating, ',');
                getline(myFile, temp.patCount, ',');
                getline(myFile, temp.contact, ',');
                getline(myFile, temp.mail);
                doctorsDataByEmail.insert({temp.mail, temp});
            }
        }
        cout << "Enter the Email of the Staff: ";
        string temp1;
        getline(cin, temp1);
        int a = doctorsDataByEmail.count(temp1);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doctorsDataByEmail.equal_range(temp1);
            for (auto itr = it.first; itr != it.second; itr++)
            {
                cout << itr->second.UID << '\t' << itr->second.name << '\t' << '\t' << itr->second.department << '\t' << '\t' << itr->second.employType << '\t' << '\t' << itr->second.start << '\t' << '\t' << itr->second.end << '\t' << '\t' << itr->second.rating << '\t' << '\t' << itr->second.patCount << '\t' << '\t' << itr->second.contact << '\t' << '\t' << itr->second.mail
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

// #endif