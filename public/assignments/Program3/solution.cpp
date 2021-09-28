/*
* Author: Brendon Kofink
* Assignment Title:  Program Three
* Assignment Description: Approximate PI with the given formulas.
* Due Date: 09/01/2021
* Date Created: 08/24/2021
* Date Last Modified: 08/26/2021
*/
#include <iostream>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  double mult;
  double first, second;
  
  //PROCESS
  //What they share in common.
  mult = 1.0 - 1.0 / 3 + 1.0 / 5 - 1.0 / 7 + 1.0 / 9 - 1.0 / 11;
  first = 4 * mult;
  second = 4 * (mult + 1.0 / 13);

  //OUTPUT
  cout << "PI = " << first << endl;  //First formula
  cout << "PI = " << second << endl; //More exact formula

  return 0;
}