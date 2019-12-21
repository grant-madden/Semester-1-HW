
/**
 *   @file: appointment.cc
 * @author: Grant Madden
 *   @date: 12/12/19
 *  @brief: This file stores all of the class functions needed in appointment_main.cc
 */

#include "appointment.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

string intToString(int str);

//Class functions
//Getters
string Appointment::getTitle(){
    return title;
}
int Appointment::getYear(){
    return year;
}
int Appointment::getMonth(){
    return month;
}
int Appointment::getDay(){
    return day;
}
int Appointment::getTime(){     //Military time
    return time;
} 
int Appointment::getDuration(){
    return duration;
}
string Appointment::getDate(){  //Return a date in the format 2019-02-13
    string date = "";
    date += to_string(month) + "-" + to_string(day) + "-" + to_string(year);
    return date;
} 
string Appointment::getStandardTime(){
    return militaryToStandard(time);
}
//Setters
void Appointment::setTitle(string newTitle){
    title = newTitle;
}
void Appointment::setYear(int newYear){
    if (newYear >= 2019 || newYear == 1) {
        year = newYear;
    }
}
void Appointment::setMonth(int newMonth){
    if (newMonth >= 1 && newMonth <= 12) {
        month = newMonth;
    }
}
void Appointment::setDay(int newDay){
    if (newDay >= 1 && newDay <= 31) {
        day = newDay;
    }
}
void Appointment::setTime(int newTime) {
    if (newTime >= 0 && newTime <= 2400) {
        if ((newTime - 60) < ((newTime/100) * 100)){
                time = newTime;
        }
    }
}
void Appointment::setDuration(int newDuration){
    if (newDuration >= 0){
        duration = newDuration;
    }
}
void Appointment::setDate(int year, int month, int day){
    setYear(year);
    setMonth(month);
    setDay(day);
}
//Main setup
Appointment::Appointment(string appData){
    string stringPlaceholder = "";
    int barCounter = 1;

    string newTitle;
    int newMonth;
    int newDay;
    int newYear;
    int newDuration;
    int newTime;
    string newDate;
    string newStandardTime;
    

    for (size_t i = 0; i < appData.length(); i++){
        if (appData[i] != ' '){
            
            if (appData[i] == '|'){
                if (barCounter == 1){
                    newTitle = stringPlaceholder;
                    if (newTitle != "N/A" && newTitle != ""){
                         setTitle(newTitle);
                    }
                    stringPlaceholder = "";
                    barCounter++;
                }
                else if (barCounter == 2){
                    
                    newYear = stoi(stringPlaceholder);
                    if (newYear > 2018) {
                        setYear(newYear);
                    }
                    else {
                        setYear(1);
                    }
                    stringPlaceholder = "";
                    barCounter++;
                }
                else if (barCounter == 3){
                   
                    newMonth = stoi(stringPlaceholder);
                    if (newMonth >= 1 && newMonth <= 12) {
                        setMonth(newMonth);
                    }
                    else{
                        setMonth(1);
                    }
                    
                    stringPlaceholder = "";
                    barCounter++;
                }
                else if (barCounter ==  4){
                    
                    newDay = stoi(stringPlaceholder);
                    if (newDay > 0 && newDay < 32) {
                        setDay(newDay); 
                    }
                    else {
                        setDay(1);
                    }
                    stringPlaceholder = "";
                    barCounter++;
                }
                else if (barCounter == 5){
                    newStandardTime = stringPlaceholder;
                    newTime = standardToMilitary(stringPlaceholder);
                    if (newTime > 0 && newTime <= 2400) {
                        if ((newTime - 60) < ((newTime/100) * 100)){
                                setTime(newTime);
                        }
                        else{
                             setTime(0);
                        }
                    }
                    else {
                        setTime(0);
                    }
                    stringPlaceholder = "";
                    barCounter++;
                }
            }
            else {
                stringPlaceholder += appData[i];
            }
            if (barCounter == 6) {
                if (appData[i] != '-' || appData[i+1] == '-'){
                    if (appData[i] != '|' && appData[i] != ' ' && appData[i] != '-') {
                    // for (int i = 0; i < )
                    newDuration = stoi(stringPlaceholder);
                    if (newDuration > 0) {
                        setDuration(newDuration);
                    }
                }
                }
                else {
                    setDuration(0);
                }
                  

            }
            
        }
        else {
            if (stringPlaceholder.length() > 1 && appData[i + 1] != '|'){
                stringPlaceholder += appData[i];
            }
        }
        
    }
}
Appointment::Appointment() {
    title = "N/A";
    month = 1;
    day = 1;
    year = 1;
    time = 0;
    duration = 1;
}


//Helper functions
void Appointment::output(){
    cout << "Title: " << title << endl;
    cout << "Date: " << month << "/" << day << "/" << year << endl;
    cout << "Military time: " << time << endl;
    cout << "Duration: " << duration << endl;
}
int Appointment::standardToMilitary(string time){
    string timeString = "";
    string hourString = "";
    string num1200 = "1200";
    
    for (size_t i = 0; i < time.length(); i++) {
        if (tolower(time[i]) == 'a' || tolower(time[i]) == 'p' || tolower(time[i]) == 'm') {
            hourString += tolower(time[i]);
        }
    }

    if (hourString == "am"){
        for (size_t i = 0; i < time.length(); i++) {
            if (isdigit(time[i])) {
                timeString += time[i];
            }
        }
        if (stoi(timeString) < 1200) {
            return stoi(timeString);
       }
       else {
           return stoi(timeString) - 1200;
       }
    }
    else if (hourString == "pm"){
        
        for (size_t i = 0; i < time.length(); i++) {
            if (isdigit(time[i])) {
                timeString += time[i];
            }
        }
        if (stoi(timeString) < 1200){
            return stoi(timeString) + 1200;
        }
        else {
            
            return stoi(timeString);
        }
        
    }
    return 0;
}
string Appointment::militaryToStandard(int time){
    string timeString = intToString(time);
    string standardTim, zero, one, two, three;
    if (time == 0){
        return "12:00 AM";
    }
    else if ( time < 10){
        zero = timeString[0];
        standardTime = "12:0" + zero + " AM";
        return standardTime;
    }
    else if ( time < 100){
        zero = timeString[0];
        one = timeString[1];
        standardTime = "12:" + zero + one + " AM";
        return standardTime;
    }
    else if (time < 1000){
        zero = timeString[0];
        one = timeString[1];
        two = timeString[2];
        standardTime =  zero + ":" + one + two + " AM";
        return standardTime;
    }
    else if (time < 1200){
        zero = timeString[0];
        one = timeString[1];
        two = timeString[2];
        three = timeString[3];
        standardTime =  zero + one + ":" + two + three + " AM";
        return standardTime;
    }
    else {
        time -= 1200;
        string timeString = intToString(time);
            if ( time < 10){
            zero = timeString[0];
            standardTime = "12:0" + zero + " PM";
            return standardTime;
        }
        else if ( time < 100){
            zero = timeString[0];
            one = timeString[1];
            standardTime = "12:" + zero + one + " PM";
            return standardTime;
        }
        else if (time < 1000){
            zero = timeString[0];
            one = timeString[1];
            two = timeString[2];
            standardTime =  zero + ":" + one + two + " PM";
            return standardTime;
        }
        else if (time < 1200){
            zero = timeString[0];
            one = timeString[1];
            two = timeString[2];
            three = timeString[3];
            standardTime =  zero + one + ":" + two + three + " PM";
            return standardTime;
        }
    }
    return standardTime;
}
bool operator ==(const Appointment &first, const Appointment &second){
    if (first.title == second.title && first.year == second.year && first.month == second.month
             && first.day == second.day && first.time == second.time && first.duration == second.duration)
    {
        return true;
    }
    return false;
    
}

string intToString(int str){
    stringstream ss;
    ss << str;
    return ss.str();
}
