#include <bits/stdc++.h>
#include "doctor.hpp"
using namespace std;

class appointment
{
public:
    string doctorUID;
    string patientUID;
    string date;
    string time;
};
class Appointment_Directory
{
public:
    void enterAppointmentDatabase()
    {
        cout << endl;
        cout << "WELCOME TO THE Appointment Management System " << endl;
        cout << "PLEASE ENTER YOUR CHOICE " << endl;
        cout << "------------------------------------------------" << endl;
        cout << "1. Book Appointment " << endl;
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
            appointmentregister();
            break;
        }
        default:
        {
            cout << "Not a valid choice. Please Enter a valid choice." << endl;
            break;
        }
        }
    }

    int latest_available(string doc, string day)
    {
        multimap<string, appointment> dayapt;
        fstream apt_register;
        apt_register.open("Appointments.csv", ios::in);
        if (apt_register.peek() != EOF)
        {
            while (!apt_register.eof())
            {
                appointment temp;
                getline(apt_register, temp.doctorUID, ',');
                getline(apt_register, temp.patientUID, ',');
                getline(apt_register, temp.date, ',');
                getline(apt_register, temp.time, ',');
                if (temp.doctorUID == doc)
                {
                    if (temp.date == day)
                    {
                        dayapt.insert({temp.time, temp});
                    }
                }
            }
        }
        if (!dayapt.empty())
        {
            vector<int> v;
            for (auto itr = dayapt.begin(); itr != dayapt.end(); itr++)
                v.push_back(stoi(itr->first));
            if (v.size() == 24)
                return 0;
            vector<int> time_slots(24);
            int time = 1000;
            for (int i = 0; i < 24; i++)
            {
                if (time % 100 == 50)
                    time = time + 50;
                else
                    time = time + 10;
                time_slots[i] = time;
            }
            int j = 0;
            while (j < v.size() && v[j] != time_slots[j])
                j = j + 1;
            return (time_slots[j - 1]);
        }
        return (1000);
    }

    bool apt_possible(appointment data)
    {
        fstream apt_register;
        apt_register.open("Appointments.csv", ios::in);
        if (apt_register.peek() != EOF)
        {
            while (!apt_register.eof())
            {
                appointment temp;
                getline(apt_register, temp.doctorUID, ',');
                getline(apt_register, temp.patientUID, ',');
                getline(apt_register, temp.date, ',');
                getline(apt_register, temp.time, ',');
                if (temp.doctorUID == data.doctorUID && temp.date == data.date && temp.time == data.time)
                {
                    cout << "broo" << endl;
                    return false;
                }
            }
        }
        return true;
    }

    void editPatientCount(string docID)
    {

        fstream myFile;
        myFile.open("DoctorsData.csv", ios::in);
        multimap<string, DOCTOR> doc_UID;
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
                doc_UID.insert({temp.UID, temp});
            }
        }
        auto it = doc_UID.find(docID);
        if (it != doc_UID.end())
        {
            int num = stoi(it->second.patCount);
            num++;
            it->second.patCount = to_string(num);
        }
        fstream myNewFile;
        myNewFile.open("DoctorsDataNew.csv", ios::out);

        for (auto itr = doc_UID.begin(); itr != doc_UID.end(); itr++)
        {
            myNewFile << itr->second.UID << ',' << itr->second.name << ',' << itr->second.department << ',' << itr->second.employType << ',' << itr->second.start << ',' << itr->second.end << ',' << itr->second.rating << ',' << itr->second.patCount << ',' << itr->second.contact << ',' << itr->second.mail;
            if (next(itr) != doc_UID.end())
                myNewFile << "\n";
        }

        myFile.close();
        myNewFile.close();

        remove("DoctorsData.csv");
        rename("DoctorsDataNew.csv", "DoctorsData.csv");
    }
    void doctor_by_dept(string dep)
    {
        fstream myFile;
        myFile.open("DoctorsData.csv", ios::in);
        multimap<string, DOCTOR> doc_dept;
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
                doc_dept.insert({temp.department, temp});
            }
        }
        int a = doc_dept.count(dep);
        if (a != 0)
        {
            cout << "UID" << '\t' << '\t' << "NAME" << '\t' << '\t' << '\t' << "DEPT." << '\t' << '\t' << "WORK AS" << '\t' << '\t' << "START" << '\t' << '\t' << "END" << '\t' << '\t' << "RATING" << '\t' << '\t' << "TOT PAT" << '\t' << '\t' << "CONTACT NO" << '\t' << '\t' << "EMAIL"
                 << '\n';
            auto it = doc_dept.equal_range(dep);
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
    }
    void book_appointment(appointment data)
    {
        fstream apt_register;
        apt_register.open("Appointments.csv", ios::in);
        multimap<string, appointment> row_appointment;
        if (apt_register.peek() != EOF)
        {
            while (!apt_register.eof())
            {
                appointment temp;
                getline(apt_register, temp.doctorUID, ',');
                getline(apt_register, temp.patientUID, ',');
                getline(apt_register, temp.date, ',');
                getline(apt_register, temp.time, ',');
                row_appointment.insert({temp.doctorUID, temp});
            }
        }

        row_appointment.insert({data.doctorUID, data});

        fstream new_apt_register;
        new_apt_register.open("new_Appointments.csv", ios::out);

        // new_apt_register << "doctorUID" << ',' << "patient_UID" << ',' << "date" << ',' << "time"
        //           << '\n';

        for (auto itr = row_appointment.begin(); itr != row_appointment.end(); itr++)
        {
            new_apt_register << itr->second.doctorUID << ',' << itr->second.patientUID << ',' << itr->second.date << ',' << itr->second.time;
            if (itr != prev(row_appointment.end()))
                new_apt_register << "\n";
        }

        apt_register.close();
        new_apt_register.close();

        remove("Appointments.csv");
        rename("new_Appointments.csv", "Appointments.csv");
        editPatientCount(data.doctorUID);
        cout << "Appointment Successful" << endl;
    }

    void appointmentregister()
    {
        appointment temp;
        cout << "Enter the patient's UID" << endl;
        getline(cin, temp.patientUID);
        cout << "1. If you want to know all available doctor in the department" << endl;
        cout << "2. If you have the doctor's UID" << endl;
        string select;
        getline(cin, select);
        int choice = stoi(select);
        switch (choice)
        {
        case 1:
        {
            string dep;
            cout << "Enter the department" << endl;
            getline(cin, dep);
            doctor_by_dept(dep);
            cout << "Enter the doctor's UID" << endl;
            getline(cin, temp.doctorUID);
            break;
        }
        case 2:
        {
            cout << "Enter the doctor's UID" << endl;
            getline(cin, temp.doctorUID);
            break;
        }
        default:
        {
            cout << "Not a valid choice. Please Enter a valid choice." << endl;
            break;
        }
        }
        cout << "1. If you want to book your own appointment with your own convenience" << endl;
        cout << "2. If you want to book latest available appointment" << endl;
        getline(cin, select);
        choice = stoi(select);

        switch (choice)
        {
        case 1:
        {
            cout << "Enter the date and time you want to book the appointment" << endl;
            getline(cin, temp.date);
            getline(cin, temp.time);
            while (!apt_possible(temp))
            {
                cout << "Appointment not possible" << endl;
                cout << "Enter the date and time you want to book the appointment" << endl;
                getline(cin, temp.date);
                getline(cin, temp.time);
            }
            book_appointment(temp);

            break;
        }
        case 2:
        {
            string dep;
            cout << "Enter the date you want to know the latest available appointment" << endl;
            getline(cin, temp.date);
            int lat_time = latest_available(temp.doctorUID, temp.date);
            temp.time = to_string(lat_time);
            book_appointment(temp);
            break;
        }
        default:
        {
            cout << "Not a valid choice. Please Enter a valid choice." << endl;
            break;
        }
        }
    }
};