/*
 *        File: invoice.cc
 *      Author: Grant Madden
 *        Date: 9/17/19
 * Description: 
 *              This program calculates total price for hard drive orders
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[]) {

    // Declare Variables
    
    double price;
    double discount;
    double tax;
 
    double subtotal;
    double total;
    double final_total;

    int quantity;

    string brand; 
    string price_input;
    string resident_input;
    string resident;
    

    // User Input
    cout << "Enter a hard drive type (w, s) followed by the quantity: ";
    cin >> price_input;
    cin >> quantity;

        if (price_input == "w") {
            price = 90.00;
            brand = "Western Digital";

        }
        else if (price_input == "s") {
            price = 95.00;
            brand = "Seagate";
        }
        else {
            cout << "Invalid Input" << endl;
        }

    //Get if user lives in Ohio
    cout << "Do you live in Ohio (yes/no)? ";
    cin >> resident_input;
        
        if (resident_input == "yes") {
                resident = "Yes";
            }
            else if (resident_input == "no") {
                resident = "No";
            }
            else {
                cout << "Invalid Input" << endl;
            }

    // Calculate total
    total = price * quantity;

        // Consider discount 
        if (quantity >= 5) {
            discount = total * 0.05;
        }
        else {
            discount = 0.00;
        }
    
    //Get subtotal
    subtotal = total - discount;        

        if (resident == "Yes"){         // taxes
            tax = subtotal * 0.07;
        }
        else {
            tax = 0.00;
        }
    // Get final total 
    final_total =  subtotal + tax;      


    // Print Final Invoice

    cout << fixed << setprecision(2);
    cout << "Hard Drives Invoice" << endl;
    cout << "------------------------------------------------" << endl;
    cout << setw(20) << "Brand: " << brand << endl;
    cout << setw(20) << "Quantity: " << quantity << endl;
    cout << setw(20) << "Price: $" << price << endl;
    cout << setw(20) << "Ohio Resident: " << resident << endl;
    cout << setw(20) << "Total Price: $" << total << endl;
    cout << "-----------------------------------------------" << endl;
    
    cout << setw(20) << "Discount: $" << discount << endl;
    cout << setw(20) << "Subtotal: $" << subtotal << endl;
    cout << setw(20) << "Taxes: $" << tax << endl;

    cout << "================================================" << endl;
    cout << setw(20) << "Total: $" << final_total << endl;
    cout << "================================================" << endl;
    

    return 0;

}// main