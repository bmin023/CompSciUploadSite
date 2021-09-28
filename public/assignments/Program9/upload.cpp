/*
 * Author: Johann Rajadurai
 * Assignment Title: Min Max Sum Count Average
 * Assignment Description:
 * The program will calculate the min max sum count
 * with the average
 * Due Date: 9/22/21
 * Date Created: 9/20/21
 * Date Last Modified: 9/22/21
 */

/*
 * Data Abstraction:
 * We initialize our variables for usage
 * Then we initialize our output and input file.
 * Add a double for variable
 * and use string for the filename.
 *
 * Input:
 * Setup do whle loop
 * Check for errors
 *
 * Process:
 * calculate:
 * min
 * max
 * average
 * sum
 * count
 *
 * and assign to respective variables
 *
 * Output:
 * cout to console using the data
 * abstracted variables.
 *
 * Assumptions:
 * it is assumed user enters correct data
 * it is assumed the user wants to do this in a file
 * it is assumed the file is in the proper directory
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // Data Abstraction
    ofstream outputFile;
    ifstream inputFile;
    int n, count = 0, sum = 0;
    int min;
    int max;
    double average;
    string fileName;

    // Input
    // Setting up do-while loop & checking for errors
    do{
        cout << "Enter Data File Name: ";
        cin  >> fileName;
        cout << fileName << endl;
        inputFile.open(fileName);
        if(!inputFile){
            cout << "Error: File Not Open." << endl; // if txt file doesn't exist
        }
    }while(!inputFile);

    cout << endl;

    // Process
    while(inputFile >> n){
        count++;
        sum += n;

        if (count == 1) {
            min = n;
            max = n;
        }

        if (min > n) {
            min = n;
        }

        if (max < n) {
            max = n;
        }
    }

    inputFile.close();
    average = static_cast<double>(sum) / count;

    // Output
    outputFile.open("countSumReport.txt");
    cout << setprecision(2) << fixed;
    outputFile << setprecision(2) << fixed;
    cout << "Min = " << min << endl;
    cout << "Max = " << max << endl;
    cout << "Sum = " << sum << endl;
    cout << "Count = " << count << endl;
    cout << "Average = " << average << endl;

    outputFile << "Count = " << count << endl;
    outputFile << "Sum = " << sum << endl;
    outputFile << "Average = " << average << endl;

    outputFile.close();

    return 0;
}