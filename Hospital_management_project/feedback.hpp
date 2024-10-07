#include <bits/stdc++.h>
#include "appointment.hpp"

using namespace std;

class Feedback_Portal
{
    void enterFeedbackPortal();
    void ratePatient();
    void rateDoctor();
};

void Feedback_Portal ::enterFeedbackPortal()
{
    cout << endl;
    cout << "WELCOME TO THE FEEDBACK PORTAL " << endl;
    cout << "PLEASE ENTER YOUR CHOICE " << endl;
    cout << "------------------------------------------------" << endl;
    cout << "1. PRESS 1 IF YOU ARE A DOCTOR " << endl;
    cout << "2. PRESS 2 IF YOU ARE A PATIENT " << endl;
    cout << "3. PRESS 3 TO QUIT THE PROGRAM" << endl;
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
        ratePatient();
        break;
    }
    case 2:
    {
        rateDoctor();
        break;
    }
    case 3:
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

void Feedback_Portal ::ratePatient()
{
    multimap<string, appointment> appointmentDataByPatient;
    string tempDocID;
    cout << "Enter your Doctor UID." << endl;
    getline(cin, tempDocID);
    string tempPatID;
    cout << "Enter the UID of the Patient you want to Rate." << endl;
    getline(cin, tempPatID);

    fstream myFile;
    myFile.open("AppointmentData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            appointment temp;
            getline(myFile, temp.doctorUID, ',');
            getline(myFile, temp.patientUID, ',');
            getline(myFile, temp.date, ',');
            getline(myFile, temp.time, ',');
            getline(myFile, temp.rated);
            if (temp.patientUID == tempPatID && temp.doctorUID == tempDocID)
            {
                appointmentDataByPatient.insert({temp.patientUID, temp});
            }
        }

        if (appointmentDataByPatient.size() != 0)
        {
            for (auto itr = appointmentDataByPatient.begin(); itr != appointmentDataByPatient.end(); itr++)
            {
                if (itr->second.rated == '0')
                {
                }
            }
            myFile.close();
        }
        else
        {
            cout << "THIS PATIENT HAS NOT VISITED YOU YET." << endl;
            myFile.close();
        }
    }
    else
    {
        cout << "APPOINTMENT REGISTER IS EMPTY." << endl;
        myFile.close();
    }
}

void Feedback_Portal ::rateDoctor()
{
    multimap<string, appointment> appointmentDataByPatient;
    string tempPatID;
    cout << "Enter your Patient UID" << endl;
    getline(cin, tempPatID);
    string tempDocID;
    cout << "Enter the Doctor UID you want to rate." << endl;
    getline(cin, tempDocID);

    fstream myFile;
    myFile.open("AppointmentData.csv", ios::in);
    if (myFile.peek() != EOF)
    {
        while (!myFile.eof())
        {
            appointment temp;
            getline(myFile, temp.doctorUID, ',');
            getline(myFile, temp.patientUID, ',');
            getline(myFile, temp.date, ',');
            getline(myFile, temp.time, ',');
            getline(myFile, temp.rated);
            if (temp.patientUID == tempPatID && temp.doctorUID == tempDocID)
            {
                appointmentDataByPatient.insert({temp.patientUID, temp});
            }
        }

        if (appointmentDataByPatient.size() != 0)
        {
            
            myFile.close();
        }
        else
        {
            cout << "THIS PATIENT HAS NOT VISITED YOU YET." << endl;
            myFile.close();
        }
    }
    else
    {
        cout << "APPOINTMENT REGISTER IS EMPTY." << endl;
        myFile.close();
    }
}
