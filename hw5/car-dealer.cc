/**
 *   @file: car-dealer.cc
 * @author: Grant Madden
 *   @date: 11/1/2019
 *  @brief: This program allows the user to price out a car model with selected options.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

///function prototypes

//Displays menu
void displayMenu(string model, double price, vector <string> &selectedOptions);

//Asks user for option (Menu)
int getOption();

//For #1, gets model selection from user
string getModelSelection(double &price);

//For #2, gets all available options from text file
void getAvailableOptions(vector <string> &availableOptions, vector <double> &optionPrice);

//For #2, displays all available options
void displayAvailableOptions(vector <string> &availableOptions, vector <double> &optionPrice);

//For #6, exits program
void exitProgram();

//For #3, adds an option to the users package if a model is already selected
void addOption(vector <string> &availableOptions, vector <string> &selectedOptions,  string model, double &price, vector <double> &optionPrice);

//For multiple #'s. searches available options and returns a location if the target is equal to an option, otherwise returns -1
int searchAvailableOptions(vector <string> &availableOptions, int count, string target);

//Converts a string to all lowercase letters
string toLowercase(string word);

//Searches user-added options  and returns a location if the target is equal to an option, otherwise returns -1
int searchRemovableOptions(vector <string> &availableOptions, int count, string target, vector <string> &selectedOptions);

//Removes an option from user-added options
void removeOption(vector <string> &selectedOptions, double &price, vector <double> &optionPrice, vector <string> &availableOptions);

//Cancels current order removing all input
void cancelOrder(vector <string> &selectedOptions, double &price, string &model);

int main(int argc, char const *argv[]) {

    // Program variables
    vector <string> availableOptions;
    vector <string> selectedOptions;
    vector <double> optionPrice; 
    string modelSelection;
    int option; 
    double totalPrice = 0;

    // Get Initial Available Options
    getAvailableOptions(availableOptions, optionPrice);
    // Display Menu
    cout << "Bobcats Auto Dealership Order System" << endl;
    displayMenu(modelSelection, totalPrice, selectedOptions);

    while (option != 6) {
        //Select menu option via user input
        option = getOption();
        if (option == 1){
            modelSelection = getModelSelection(totalPrice);
            displayMenu(modelSelection, totalPrice, selectedOptions);
        }
        else if (option == 2){
            displayAvailableOptions(availableOptions, optionPrice);
            displayMenu(modelSelection, totalPrice, selectedOptions);
        }
        else if (option == 3){
            addOption(availableOptions, selectedOptions, modelSelection, totalPrice, optionPrice);
            displayMenu(modelSelection, totalPrice, selectedOptions);
        }
        else if (option == 4){
            removeOption(selectedOptions, totalPrice, optionPrice, availableOptions);
            displayMenu(modelSelection, totalPrice, selectedOptions);
        }
        else if (option == 5){
            cancelOrder(selectedOptions, totalPrice, modelSelection);
            displayMenu(modelSelection, totalPrice, selectedOptions);
        }
        //exit program
        else if (option == 6){
            exit(EXIT_SUCCESS);
        }
    }
        
    return 0;
}
// 5 
void cancelOrder(vector <string> &selectedOptions, double &price, string &model){
    for (unsigned int i = 0; i < selectedOptions.size(); i++){
        selectedOptions[i].erase();
    }
    price = 0;
    model = "N";
    return;
}
// 4
void removeOption(vector <string> &selectedOptions, double &price, vector <double> &optionPrice, vector <string> &availableOptions){
    string inputOption; 
    // unsigned int count = selectedOptions.size();
    cout << "Enter a option to remove: ";
    getline(cin, inputOption, '\n');
    
    int searchedOption = searchRemovableOptions(availableOptions, 15, inputOption, selectedOptions);
    
    if (searchedOption != -1) {
        selectedOptions.erase(selectedOptions.begin() + searchedOption);
        int priceLocation = searchAvailableOptions(availableOptions, 15, inputOption);
        price = price - optionPrice[priceLocation];
        return;
    }
    else {
        cout << "Invalid Input, " << inputOption << "  is not a selected option" << endl;
        return;
    }
}
    int searchRemovableOptions(vector <string> &availableOptions, int count, string target, vector <string> &selectedOptions){ 
        // int searchedOption;
        int first = 0;
        unsigned int unsignedFirst = first;
        int last = count - 1;
        string a = "a";
        string targetLower;
        string optionLower = "";
        while (first <= last) {
            if (unsignedFirst < selectedOptions.size()){
                cout << "EXIT";
                optionLower = toLowercase(selectedOptions[first]);
            } 
            else {
                return -1;
            }
            targetLower = toLowercase(target);
            
            if (targetLower == optionLower){
                return first;
            }
            first++;
            unsignedFirst++;
        }
        return -1;
    }
// 3
void addOption(vector <string> &availableOptions, vector <string> &selectedOptions,
    string model, double &price, vector <double> &optionPrice){
    string option;
    string cancel = "cancel";
     if (toLowercase(model) == "e" || toLowercase(model) == "l" || toLowercase(model) == "x"){
    }
    else {
        cout << "No model selected, select a model first to add options" << endl;
        return;
    }
    cout << "Enter an option to add it: ";
    getline(cin, option, '\n');
    
    int output = searchAvailableOptions(availableOptions, 45, option);
    // Check for valid option
    while (output == -1 && option != cancel){
        cout << "Invalid input, enter a valid option or enter cancel to go back to the main menu: ";
        getline(cin, option, '\n');
        
        output = searchAvailableOptions(availableOptions, 15, option);
    }
   if (option == cancel){
       return;
   }
    cout << "You added " << availableOptions[output] << endl;
    
            
    selectedOptions.push_back(availableOptions[output]);
    price = price + optionPrice[output];

    availableOptions.erase(availableOptions.begin() + output);
    return; 
}
    int searchAvailableOptions(vector <string> &availableOptions, int count, string target){
        int first = 0, last = count - 1;
        string targetLower;
        string optionLower;
        while (first <= last) {
            optionLower = toLowercase(availableOptions[first]);
            targetLower = toLowercase(target);
            
            if (targetLower == optionLower){
                return first;
            }
            first++;
        }
        
        return -1;
    }
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
// 2
void displayAvailableOptions(vector <string> &availableOptions, vector <double> &optionPrice){
    int optionCounter = 0;
   
    cout << "Available Options: \n" << endl;
    
    for (int x = 0; x < 5; x++) {

        for (int i = 0; i < 3; i++){
            cout << fixed << setprecision(2);
            int conversion = optionPrice[optionCounter];
            string output = availableOptions[optionCounter] + " ($" + to_string(conversion)  + ")";
            cout << left << setw(30) << output;
            

            optionCounter++;
            
        }
        cout << endl;
    }
    cout << endl;
    return;
}
// Menu
void displayMenu(string model, double price, vector <string> &selectedOptions){
    cout << "Main Menu: \n";
    string modelE = "E", modelL = "L", modelX = "X";

    if (toLowercase(model) == "e"){
        cout << setprecision(2) << "Model: E - Total Price: $"  << price << " - Options: ";
        for (size_t i = 0; i < selectedOptions.size(); i++){
            if ( i == 0){
                cout << selectedOptions[i];
            }
            else {
                cout << ", " << selectedOptions[i];
            }
        }
        cout << endl;
        
    }
    else if (toLowercase(model) == "l"){
        cout << setprecision(2) << "Model: L - Total Price: $"  << price << " - Options: ";
        for (size_t i = 0; i < selectedOptions.size(); i++){
            if ( i == 0){
                cout << selectedOptions[i];
            }
            else {
                cout << ", " << selectedOptions[i];
            }
        }
        cout << endl;
    }
    else if (toLowercase(model) == "x"){
        cout << setprecision(2) << "Model: X - Total Price: $"  << price << " - Options: ";
        for (size_t i = 0; i < selectedOptions.size(); i++){
            if ( i == 0){
                cout << selectedOptions[i];
            }
            else {
                cout << ", " << selectedOptions[i];
            }
        }
        cout << endl;
    }
    else {
        cout << "NO MODEL SELECTED" << endl;
    }

    cout << "1) Select a model (E, L, X)" << endl;
    cout << "2) Display available options and prices" << endl;
    cout << "3) Add an option" << endl;
    cout << "4) Remove an option" << endl;
    cout << "5) Cancel order" << endl;
    cout << "6) Quit\n" << endl;
    return;
}
// 1
string getModelSelection(double &price){
    string model;
    string modelE = "E", modelL = "L", modelX = "X";
    
    bool exitLoop = false;
    cout << fixed << left;
    cout << setw(9) << "Model:" << setw(10) << "Base Price" << endl;
    cout << setw(9) << "E" << setw(10) << "$10,000.00" << endl;
    cout << setw(9) << "L" << setw(10) << "$12,000.00" << endl;
    cout << setw(9) << "X" << setw(10) << "$18,000.00" << endl;

    cout << "Enter E, L, or X: ";
    getline(cin, model, '\n');
    while (!exitLoop) {
        if (toLowercase(model) == toLowercase(modelE)) {
            cout << "You chose model E\n"<< endl;
            price = 10000;
            exitLoop = true;
            
        }
        else if (toLowercase(model) == toLowercase(modelL)) {
            cout << "You chose model L\n"<< endl;
            price = 120000;
            exitLoop = true;
        }
        else if (toLowercase(model) == toLowercase(modelX)) {
            cout << "You chose model X\n"<< endl;
            price = 18000;
            exitLoop = true;
        }
        else {
            cout << "Select a valid option: ";
            getline(cin, model, '\n');
        }
    }
    return model;
}
// Number Selector
int getOption(){
    int returnOption;
    string option;
    string option1 = "1", option2 = "2", option3 = "3", option4 = "4", option5 = "5", option6 = "6";

    bool exitLoop = false;
    cout << "Enter an option: ";
    getline(cin, option, '\n');
    while (!exitLoop) {
        if (option == option1) {
            exitLoop = true;
            returnOption = 1;
            cout << "\nYou chose option #1 - Select a model (E, L, X)" << endl;
            
        }
        else if (option == option2) {
            cout << "\nYou chose option #2 - Display available options and prices" << endl;
            exitLoop = true;
            returnOption = 2;
        }
        else if (option == option3) {
            cout << "\nYou chose option #3 - Add an options" << endl;
            exitLoop = true;
            returnOption = 3;
        }
        else if (option == option4) {
            cout << "\nYou chose option #4 - Remove an options" << endl;
            exitLoop = true;
            returnOption = 4;
        }
        else if (option == option5) {
            cout << "\nYou chose option #5 - Cancel order" << endl;
            exitLoop = true;
            returnOption = 5; 
        }
        else if (option == option6) {
            cout << "\nYou chose option #6 - Quit\n" << endl;
            exitLoop = true;
            returnOption = 6;
        }
        else {
            cout << "\nInvalid option \n\n";
            cout << "1) Select a model (E, L, X)" << endl;
            cout << "2) Display available options and prices" << endl;
            cout << "3) Add an options" << endl;
            cout << "4) Remove an options" << endl;
            cout << "5) Cancel order" << endl;
            cout << "6) Quit\n" << endl;
            cout << "Enter a valid option: ";
            getline(cin, option, '\n');
        }
    }
    return returnOption;
}
// get vectors
void getAvailableOptions(vector <string> &availableOptions, vector <double> &optionPrice){
    string option;
    ifstream inStream;
    double curPrice;

    inStream.open("options.txt"); //connect stream to file
    if (inStream.fail()) //check for failure to open
    {
        cout << "File failed to open" << endl;
    }
    for (int i = 0; i < 45; i++){
        inStream >> curPrice;
        inStream >> ws;
        getline(inStream, option);
        optionPrice.push_back(curPrice);
        availableOptions.push_back(option);
    }
    inStream.close();
}