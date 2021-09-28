/*
* Author: Brendon Kofink
* Assignment Title:  Program 4
* Assignment Description: Sum the Digits in an integer.
* Due Date: 09/03/2021
* Date Created: 08/27/2021
* Date Last Modified: 9/01/2021
*/

/*
* Data Abstraction:
*		An int to hold the input, and an int to keep hold of the total.
* Input: 
*		Pull in the user's int between 0 and 9999999.
* Process:
*		Mod 10, add it to the total, divide and set by 10. Repeat 7 times.
* Output:
*		Output the final total
* Assumptions:
*		It is assumed the user's input is an integer between 0 and 9999999.
*/

#include <iostream>

using namespace std;

int main()
{
  //Data Abstraction
  int input;
  int total = 0;

  //Input
  cin >> input;
  //Echo it back
  cout << "Enter an integer between 0 and 9999999: " << input << endl;

  //Process
  //A better solution would have been to stick the two lines in a for loop.
  //But I don't know if I could use code we haven't covered in the book yet.
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;
  total += input % 10;
  input /= 10;

  //Output
  cout << "The sum of the digits is " << total << ".";

  return 0;
}