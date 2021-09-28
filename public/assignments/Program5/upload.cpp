/*
* Author: Brendon Kofink
* Assignment Title:  Program Five
* Assignment Description: Return the arithmetic mean, geometric mean,
* harmonic mean, and standard deviation given 5 numbers,
* Due Date: 09/08/2021
* Date Created: 08/30/2021
* Date Last Modified: 09/05/2021
*/

/*
 * Data Abstraction:
 *    Five ints, a,b,c,d,e, one for each inputted number.
 *    A temp variable for sorting, 
 *    Then four variables to hold my outputs, labeled after each. 
 * Input: 
 * 		Set a,b,c,d,e to their respective inputs using cin.
 * Process:
 * 		First, sort the values from greatest to least. 
 *    Starting with the first variable and going down, 
 *      swapping up until it reaches the correct spot.
 *    Then set the formulas to the correct values, 
 *      keeping in mind integer overflow.
 * Output: 
 * 		Print the sorted order then the formulas.
 * Assumptions: 
 * 		It is assumed the user will input 5 positive integers.
 */
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION:

  //These are our five inputs.
  unsigned int a, b, c, d, e;
  //Amount of inputs, constant since assumed to be 5
  const double n = 5.0;
  double mean, geometricMean, harmonicMean, standardDeviation;
  //For sorting
  int temp;
  //INPUT:

  //Echo it back
  cout << "Enter five numbers:" << endl;
  cin >> a >> b >> c >> d >> e;
  cout << a << endl; //Echo Print
  cout << b << endl; //Echo Print
  cout << c << endl; //Echo Print
  cout << d << endl; //Echo Print
  cout << e << endl; //Echo Print
  cout << endl << endl << endl; //A little space.
  //PROCESS:

  //First sort them.
  //We've only learned if statements so far.
  //So this is not going to be pretty code.
  //First, nothing.
  //Second
  if (b > a)
  {
    temp = a;
    a = b;
    b = temp;
  }
  //Third
  if (c > b)
  {
    temp = b;
    b = c;
    c = temp;
    if (b > a)
    {
      temp = a;
      a = b;
      b = temp;
    }
  }
  //Fourth
  if (d > c)
  {
    temp = c;
    c = d;
    d = temp;
    if (c > b)
    {
      temp = b;
      b = c;
      c = temp;
      if (b > a)
      {
        temp = a;
        a = b;
        b = temp;
      }
    }
  }
  //Fifth
  if (e > d)
  {
    temp = d;
    d = e;
    e = temp;
    if (d > c)
    {
      temp = c;
      c = d;
      d = temp;
      if (c > b)
      {
        temp = b;
        b = c;
        c = temp;
        if (b > a)
        {
          temp = a;
          a = b;
          b = temp;
        }
      }
    }
  }
  mean = (a + b + c + d + e) / n;
  geometricMean = pow((static_cast<double>(a) * b * c * d * e), (1 / n));

  harmonicMean = n / 
    ((1.0 / a) + (1.0 / b) + (1.0 / c) + (1.0 / d) + (1.0 / e));

  standardDeviation = pow(
      (pow(a - mean, 2) + pow(b - mean, 2) + pow(c - mean, 2) + 
      pow(d - mean, 2) + pow(e - mean, 2)) / n, 0.5);

  //OUTPUT:

  cout << "Result:" << endl
       << endl;
  //Print the numbers, now sorted
  cout << "Data:" << endl;
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << d << endl;
  cout << e << endl << endl;

  cout << fixed << setprecision(2);

  cout << "Arithmetic Mean    = " << mean << endl;
  cout << "Geometric  Mean    = " << geometricMean << endl;
  cout << "Harmonic   Mean    = " << harmonicMean << endl;
  cout << "Standard Deviation = " << standardDeviation << endl;

  return 0;
}