/*
 *        File: ancient-mult.cc
 *      Author: Author
 *        Date: Date
 * Description: This program multiplies  two numbers using an ancient multiplication process
 * and displays the output. 
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm> 
#include <string>  
using namespace std;

//function prototypes

int main(int argc, char const *argv[]) 
{

    // Variables
    int x;
    int y;
    int x2;
    int y2;
    int count = 0;
    char quit;
    

    
    do {
        cout << "Ancient Multiplication" << endl;

        // Get first user input
        cout << "Enter a positive integer: ";
        cin >> x;

            //Check for invalid input
            while (x < 0) {
                cout << "Invalid input. Enter a positive integer: ";
                cin >> x; 
            }
        
        // Get secont user input
        cout << "Enter a second positive integer: ";
        cin >> y;
        
            while (y < 0){
                cout << "Invalid input, Enter a second positive integer: ";
                cin >> y;
            }
        //Copy x and y
        x2 = x;
        y2 = y;
        

    // Ancient multiplication
            while (y != 0) {

                    if (y % 2 != 0) {
                        count = count + x;
                    }

                x = x * 2;
                y = y / 2;
            } 

     // Output   
        cout << x2 << " * " << y2 << " = " << count << endl;
        cout << "Press any key to continue, or \"Q\" to quit: ";
        cin >> quit;

        if (quit == 'q'){
            quit = 'Q';
        }

    }   while (quit != 'Q');

    return 0;

}// main