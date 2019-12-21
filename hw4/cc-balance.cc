/**
 *   @file: cc-balance.cc
 * @author: Grant Madden
 *   @date: 10/21
 *  @brief: this program sorts credit card data from a file and outputs certain items to a new file based on user input. 
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

///function prototypes

/**
 *  Function:   isValidOption
 *              returns true if option is valid
 *
 *  @param option - user inputted string used to select an option
 *  @return - true or false
 */

bool isValidOption(string option); 

/**
 *  Function:   processBalance
 *              Handles options -a and -b
 *              -a: outputs all customers with a balance equal to or higher than specified balance
 *              -b: outputs all customers with a balance equal to or lower than specified balance
 *
 *  @param option - user inputted string used to select an option
 *  @param balance - user inputted balance used in comparison to all inputted balances
 *  @param inStream - input stream
 *  @param ofStream - output stream
 */
void processBalance(string option, double balance, ifstream &inStream, ofstream &outStream);

/**
 *  Function:   processBalanceDue
 *              Handles option -d, outputs all customers with a balance due within the amount of days specified
 *
 *  @param numDays - number of days specified
 *  @param inStream - input stream
 *  @param ofStream - output stream
 */
void processBalanceDue(int numDays, ifstream &inStream, ofstream &outStream);

/**
 *  Function:   outputSummary
 *              Handles option -A, displays all records as well as the average balance and total of all balances
 *
 *  @param inStream - input stream
 *  @param ofStream - output stream
 */
void outputSummary(ifstream &inStream, ofstream &outStream); 

int main(int argc, char const *argv[]) {

    // Check number of arguments
    if (argc != 4 && argc != 5){
        cout << "Invalid arguments" << endl;
        return 0;
    }

    //Variables
    string option = argv[1];
    string balanceInput = argv[2];
    string stringDays = argv[2];
    ifstream inStream;
    ofstream outStream;
    bool validOption;

    // Check option
    validOption = isValidOption(option);
    if (!validOption){
        cout << "Invalid option" << endl;
        return 0;
    }
    
    // Open input and output files and check for failure
    if (argc == 5){
        inStream.open(argv[3]); 
        if (inStream.fail()) 
        {
            cout << "Failed to open input file" << endl;
            return 0;
        }
        outStream.open(argv[4]); 
        if (outStream.fail()) 
        {
            cout << "Failed to open output file" << endl;
            return 0;
        }
    } else if (argc == 4){
        inStream.open(argv[2]); 
        if (inStream.fail()) 
        {
            cout << "Failed to open input file" << endl;
            return 0;
        }
        outStream.open(argv[3]); 
        if (outStream.fail()) 
        {
            cout << "Failed to open output file" << endl;
            return 0;
        }
    }
    // Determine which function to use and call it
    if (argc == 5){
        if (option == "-a" || option == "-b") {
            double balance = stod(balanceInput);
            processBalance(option, balance, inStream, outStream);
        }
        else if (option == "-d"){
            int days = stoi(stringDays);
            processBalanceDue(days, inStream, outStream);
        }
        else {
            cout << "Error";
            return 0;
        }
    }
    else if (argc == 4){
        if (option == "-A"){
            outputSummary(inStream, outStream);
        }
        else {
            cout << "Error";
            return 0;
        }
    }

    // Close input and output streams
    inStream.close();
    outStream.close();

    return 0;

}/// main

bool isValidOption(string option){
    if (option == "-a" || option == "-b" || option == "-d" || option == "-A"){
        return true;
    }
    else {
        return false;
    }
}
void processBalance(string option, double balance, ifstream &inStream, ofstream &outStream){
    string id, first, last, space;
    double currentBalance;
    int days;

    if (option == "-a"){
        
        outStream << fixed << left << setprecision(2);
        outStream << "All customers with a balance equal to or higher than specified balance ($" << balance << "): " << endl;
        outStream << setw(15) << "Id: " << setw(15) << "First: " << setw(15) << "Last: " << setw(15) << "Balance: " << setw(15) << "Days: " << endl;
        
        inStream >> id >> first >> last >> currentBalance >> days;

        while (!inStream.eof()){
            if (currentBalance >= balance){
                outStream << setw(15) << id << setw(15) << first << setw(15) << last << setw(15) << currentBalance << setw(15) << days << endl;
                inStream.clear();
            }
            inStream >> id >> first >> last >> currentBalance >> days;
        }
    }
    else if (option == "-b"){
        outStream << fixed << left << setprecision(2);
        outStream << "All customers with a balance equal to or less than than specified balance ($" << balance << "): " << endl;
        outStream << setw(15) << "Id: " << setw(15) << "First: " << setw(15) << "Last: " << setw(15) << "Balance: " << setw(15) << "Days: " << endl;
        
        inStream >> id >> first >> last >> currentBalance >> days;

        while (!inStream.eof()){
            if (currentBalance <= balance){
                outStream << setw(15) << id << setw(15) << first << setw(15) << last << setw(15) << currentBalance << setw(15) << days << endl;
                inStream.clear();
            }
            inStream >> id >> first >> last >> currentBalance >> days;
        }
    }
}
void processBalanceDue(int numDays, ifstream &inStream, ofstream &outStream){
        string id, first, last, space;
        double currentBalance;
        int days;

        outStream << fixed << left << setprecision(2);
        outStream << "All customers with a balance due within "<< numDays << " days:" << endl;
        outStream << setw(15) << "Id: " << setw(15) << "First: " << setw(15) << "Last: " << setw(15) << "Balance: " << setw(15) << "Days: " << endl;
        
        inStream >> id >> first >> last >> currentBalance >> days;

        while (!inStream.eof()){
            if (days <= numDays && currentBalance != 0){
                outStream << setw(15) << id << setw(15) << first << setw(15) << last << setw(15) << currentBalance << setw(15) << days << endl;
                inStream.clear();
            }
            inStream >> id >> first >> last >> currentBalance >> days;
        }
}
void outputSummary(ifstream &inStream, ofstream &outStream){
    string id, first, last, space;
        double currentBalance;
        int days;
        double totalBalance = 0;           
        double averageCounter = 0;
        outStream << fixed << left << setprecision(2);
        outStream << "All customers + Average and Total Balances " << endl;
        outStream << setw(15) << "Id: " << setw(15) << "First: " << setw(15) << "Last: " << setw(15) << "Balance: " << setw(15) << "Days: " << endl;
        
        inStream >> id >> first >> last >> currentBalance >> days;

        while (!inStream.eof()){
            
            outStream << setw(15) << id << setw(15) << first << setw(15) << last
                 << setw(15) << currentBalance << setw(15) << days << endl;

            totalBalance = totalBalance + currentBalance;
            inStream >> id >> first >> last >> currentBalance >> days;
                if (inStream.eof()){
                    double averageBalance = totalBalance / averageCounter;
                    outStream << setw(15) << "Average Balance: " << setw(15) << averageBalance 
                        << setw(15) << "Total Balance:  " <<setw(15) << totalBalance << endl;
                    
                }
            averageCounter++;
        }
        
}