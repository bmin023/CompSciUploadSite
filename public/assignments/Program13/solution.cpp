/*
* Author: Brendon Kofink
* Assignment Title:  Program 13
* Assignment Description: Print the nth number in Fibonacci using arrays
* Due Date: 10/05/2021
* Date Created: 09/30/2021
* Date Last Modified: 09/30/2021
*/

/*
* Data Abstraction:
*    A const to hold how many fib numbers to store.
*    An int to hold how many values and an array to hold the values of fib.
* Input:
*    Get how many inputs there are.
* Process:
*    (Technically preprocess)
*    Create an array of all the values of the fibonacci sequence.
*    Using the formula f(n) = f(n-1) + f(n-2) 
* Output:
*    Output the fibonacci of each of the inputs as you go through them.
* Assumptions:
*    
*/

#include <iostream>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  const int SIZE = 100;
  int numValues;
  int input; //For later inputs.
  unsigned long long int fib[SIZE];

  //PROCESS

  //Initialize the array's first values.
  fib[0] = 0;
  fib[1] = 1;

  //Create the fibonnacci array.
  for (int i = 2; i < SIZE; i++)
  {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  //INPUT
  cin >> numValues;
  for (int i = 0; i < numValues;i++) {

  }
  //OUTPUT

  for (int i = 0; i < numValues; i++) {
    cin >> input;
    cout << "case " << i + 1 << ": Fib(" << input << ") = ";
    cout << fib[input] << endl;
  }  

  return 0;
}