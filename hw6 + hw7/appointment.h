
/**
 *   @file: appointment.h
 * @author: Grant Madden
 *   @date: 12/12/19
 *  @brief: This file declares the appointment class
 */

#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Appointment {
    public:
        //Constructors
        Appointment();
        Appointment(string appData);

        //Getter/Accessor
        string getTitle();
        int getYear();
        int getMonth();
        int getDay();
        int getTime(); //Military time
        int getDuration();
        string getDate(); //Return a date in the format 2019-02-13
        string getStandardTime();

        //Setter/Mutator
        void setTitle(string newTitle);
        void setYear(int newYear);
        void setMonth(int newMonth);
        void setDay(int newDay);
        void setTime(int newTime); //Military time
        void setDuration(int newDuration);
        void setDate(int year, int month, int day);

        //Helper functions
        void output();
        string militaryToStandard(int time);
        int standardToMilitary(string time);
        friend bool operator ==(const Appointment &first, const Appointment &second);

    private:
        string title;
        int month;
        int day;
        int year;
        int time;
        int duration;
        string date;
        string standardTime;

};
#endif
