
/**
 *   @file: appointment_main.cc
 * @author: Grant Madden
 *   @date: 12/12/19
 *  @brief: This program allows you to keep track of and edit an appointment text file
 */

#include "appointment.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <ctype.h>

using namespace std;

///function prototypes

//Get appointments from file
void getAppointments(vector <Appointment> &allAppointments, ifstream &inStream);
//Send appointments to file
void sendAppointments(vector <Appointment> &allAppointments, ofstream &outStream);

//Option -ps - Print my daily schedule in order by starting time using standard time format. 
void sortByTime(vector <Appointment> &allAppointments);
int indexOfSmallest(vector <Appointment> &allAppointments, int startIndex, int endIndex);
void printAppointments(vector <Appointment> &allAppointments);
//Option -p - Print all appointments at specified military time
void printByTime(vector <Appointment> &allAppointments, string militaryTime);
//Option -a - Add an appointment
void addAppointments(vector <Appointment> &allAppointments, string appData);
//Option -dt - Delete all appointments that match a title exactly
void removeTitle(vector <Appointment> &allAppointments, string title);
//Option -dm - Delete a all appointments that match the starting military time exactly
void removeTime(vector <Appointment> &allAppointments, int time);

// Other functions
    //Converts strings to lowercase
    string toLowercase(string word);

//Main function
int main(int argc, char const *argv[]) {
    //Variables
    string printSchedule = "-ps",  printTime = "-p",  addAppointment = "-a",
         deleteTitle = "-dt",  deleteTime = "-dm";
    ifstream inStream;
    ofstream outStream;
    vector <Appointment> allAppointments;

    // Open file
    inStream.open("data.txt"); //connect stream to file
        if (inStream.fail()){ //check for failure to open
            cout << "File failed to open" << endl;
        }
    

    //Get vector
    getAppointments(allAppointments, inStream);
    if (allAppointments.size() == 0){
        return 0;
    }

    // Check for invalid arguments
    if (argc != 2 && argc != 3) {
        cout << "Invalid Arguments" << endl;
        return 0;
    }
    
    
    //Option select
    if (argc == 2){
        // option -ps
        if (argv[1] == printSchedule){
            sortByTime(allAppointments);
            printAppointments(allAppointments);
        }
        else {
            cout << "Invalid option" << endl;
        }
    }
    else if (argc == 3){
        if (argv[1] == printTime){ // option -p
            printByTime(allAppointments, argv[2]);
        }
        if (argv[1] == addAppointment){ // option -a
            addAppointments(allAppointments, argv[2]);
            
        }
        if (argv[1] == deleteTitle){ // option -dt
            removeTitle(allAppointments, argv[2]);
        }
        if (argv[1] == deleteTime){ // option -dm 
            int time = stoi(argv[2]);
            removeTime(allAppointments, time);
        }
        
    }
    
    //Close Input Stream
    inStream.close();

    //Open output file
    outStream.open("data.txt"); 
        if (outStream.fail()){
            cout << "Failed to open output file" << endl;
            return 0;
        }
    //Export appointments
    sendAppointments(allAppointments, outStream);


    //Close Output Stream
    outStream.close();
    return 0;

}

//Get appointments from file
void getAppointments(vector <Appointment> &allAppointments, ifstream &inStream){
    string inputData;
    string appData = "";
   while (!inStream.eof()){
       getline(inStream, inputData);
       for (size_t i = 0; i < inputData.size(); i++){
           if (!isspace(inputData[i])){
               appData += inputData[i];
           }
       }
       if (appData != "" && appData != " "){
            Appointment a(inputData);
            allAppointments.push_back(a);
            appData = "";
       }
   }
}
//Send appointments to file
void sendAppointments(vector <Appointment> &allAppointments, ofstream &outStream){
    int x = 0;
    cout << "worked\n";
    for (size_t i = 0; i < allAppointments.size(); i++){
        outStream << allAppointments[x].getTitle() << " | ";
        outStream << allAppointments[x].getYear() << " | " << allAppointments[x].getMonth() << " | " << allAppointments[x].getDay() << " | ";
        outStream << allAppointments[x].getStandardTime() << " | ";
        outStream << allAppointments[x].getDuration() << endl;
        
        x++;
    }
}
//Option -ps
void sortByTime(vector <Appointment> &allAppointments){
    int minIndex;
    Appointment temp;


    for (size_t i = 0; i < allAppointments.size() - 1; i++){
        minIndex = indexOfSmallest(allAppointments, i, allAppointments.size());
        temp = allAppointments[minIndex];
        allAppointments[minIndex] = allAppointments[i];
        allAppointments[i] = temp;
    }
    return;
}
int indexOfSmallest(vector <Appointment> &allAppointments, int startIndex, int endIndex){
    int min = allAppointments[startIndex].getTime();
    int minIndex = startIndex;

    for (int i = startIndex; i < endIndex; i++){
        if (allAppointments[i].getTime() < min){
            min = allAppointments[i].getTime();
            minIndex = i;
        }
    }
    return minIndex;

}
void printAppointments(vector <Appointment> &allAppointments){
    int x = 0;
    for (size_t i = 0; i < allAppointments.size(); i++){
        cout << "Title: " << allAppointments[x].getTitle() << endl;
        cout << "Date: " <<  allAppointments[x].getMonth() << "/" << allAppointments[x].getDay() << "/" << allAppointments[x].getYear() << endl;
        cout << "Military time: " << allAppointments[x].getTime() << endl;
        cout << "Duration: " << allAppointments[x].getDuration() << endl;
        cout << endl;
        x++;
    }
}
//Option -p
void printByTime(vector <Appointment> &allAppointments, string militaryTime){
   int time = stoi(militaryTime);
    for (size_t i = 0; i < allAppointments.size() - 1; i++){
        if (allAppointments[i].getTime() == time){
            allAppointments[i].output();
        }
    }
}
//Option -a
void addAppointments(vector <Appointment> &allAppointments, string appData){
    Appointment a(appData);
    allAppointments.push_back(a);
    return;
}
//Option -dt
void removeTitle(vector <Appointment> &allAppointments, string title){
    string appointmentTitle, inputTitle;
    for (size_t i = 0; i < allAppointments.size(); i++){
        appointmentTitle = toLowercase(allAppointments[i].getTitle());
        inputTitle = toLowercase(title);

        if (appointmentTitle == inputTitle){
            allAppointments.erase(allAppointments.begin() + i);
        }
    }
    return;
}
//Option -dm
void removeTime(vector <Appointment> &allAppointments, int time){
    for (size_t i = 0; i < allAppointments.size(); i++){
    
        if (allAppointments[i].getTime() == time){
            allAppointments.erase(allAppointments.begin() + i);
        }
    }
    return;
}
//Other functions
string toLowercase(string word){
    unsigned int i=0;
    char c;
    string newWord = "";
    while (i < word.length())
    {
        c=word[i];
        
        newWord += tolower(c);
        i++;
    }
    return newWord;
}
