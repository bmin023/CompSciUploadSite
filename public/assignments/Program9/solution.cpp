/*
* Author: Brendon Kofink
* Assignment Title:  Program 9
* Assignment Description: Get the Min, Max, Sum, Count,
*     and Average of numbers in a file.
* Due Date: 09/22/2021
* Date Created: 09/14/2021
* Date Last Modified: 09/15/2021
*/

/*
* Data Abstraction:
*    Declare an ifstream and an int for individual inputs. 
*    Declare ints for each output except average which is a double.
* Input:
*    Set up the input file, using cin to get the file name. A while loop
*      checks if the file is good.
* Process:
*    Create a loop that terminates when it doesn't find any more input
*      from the file. It calculates min, max, sum, count, and average
*      This is the third time, so the method is well known.
* Output:
*    Output the min, max, sum, count, and average in that order.
* Assumptions:
*    It is assumed the file contains only integers.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION

  string fileName;
  ifstream file;

  int input;
  //Initialized to one because I take one input early.
  int count = 1;
  int sum;
  int min, max;
  double average = 0;

  //INPUT

  //open the file based on input, make sure it's a file
  do
  {
    cout << "Enter Data File Name: ";
    cin >> fileName;
    cout << fileName << endl; //Echo it back.
    file.open(fileName);
    if(!file) {
      cout << "Error: File Not Open." << endl;
    }
  } while (!file);
  cout << endl;
  
  //PROCESS

  //Get the first input to initialize min and max.
  file >> input;
  min = input;
  max = input;
  sum = input;

  //Start the loop. get INPUT then PROCESS.
  while (file >> input)
  {
    //Process
    if (input > max)
    {
      max = input;
    }
    else if (input < min)
    {
      min = input;
    }
    count++;
    sum += input;
  }

  //Calculate average
  average = static_cast<double>(sum) / count;

  file.close();

  //OUTPUT

  cout << fixed << setprecision(2);

  cout << "Min = " << min << endl;
  cout << "Max = " << max << endl;
  cout << "Sum = " << sum << endl;
  cout << "Count = " << count << endl;
  cout << "Average = " << average << endl;

  return 0;
}