#include <bits/stdc++.h>
#include "doctor.hpp"
#include "patient.hpp"
// #include "appointment.hpp"

using namespace std;

// void HOME_PAGE(Doctors_Directory &Doctors_Data, Patients_Directory &Patients_Data, Appointment_Directory &Appointment_Data)
void HOME_PAGE(Doctors_Directory &Doctors_Data, Patients_Directory &Patients_Data)
{
    cout << endl;
    cout << "WELCOME TO IIT HYDERABAD HOSPITAL HELP-DESK PORTAL " << endl;
    cout << "PLEASE ENTER YOUR CHOICE " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. Doctors Directory" << endl;
    cout << "2. Patients Directory" << endl;
    cout << "3. Appointment Management System" << endl;
    cout << "4. Feedback Management Portal" << endl;
    cout << "5. Exit" << endl;
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
        Doctors_Data.enterDoctorDatabase();
        // HOME_PAGE(Doctors_Data, Patients_Data, Appointment_Data);
        HOME_PAGE(Doctors_Data, Patients_Data);
        break;
    }
    case 2:
    {
        Patients_Data.enterPatientDatabase();
        // HOME_PAGE(Doctors_Data, Patients_Data, Appointment_Data);
        HOME_PAGE(Doctors_Data, Patients_Data);
        break;
    }
    // case 3:
    // {
    //     Appointment_Data.enterAppointmentDatabase();
    //     HOME_PAGE(Doctors_Data, Patients_Data, Appointment_Data);
    //     break;
    // }
    case 4:
    {
    }
    case 5:
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

int main()
{

    Doctors_Directory Doctors_Data;
    Patients_Directory Patients_Data;
    // Appointment_Directory Appointment_Data;

    // HOME_PAGE(Doctors_Data, Patients_Data, Appointment_Data);
    HOME_PAGE(Doctors_Data, Patients_Data);

    return 0;
}