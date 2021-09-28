/*
* Author: Brendon Kofink
* Assignment Title:  Program Seven
* Assignment Description: Given five grades, 
*    output average, min, max, median, and letter grade.
* Due Date: 09/07/2021
* Date Created: 09/07/2021
* Date Last Modified: 09/07/2021
*/

/*
* Data Abstraction:
*    doubles a-e for storing inputs, 
*    doubles for holding all outputs (average and grade)
*    temp for sorting, error to stop errors.
* Input:
*    Grab five inputs, feed them to a-e.
* Process:
*    To get the median, sort the variable and take the third.
*    Min is the last. Max is the first.
*    Average is the normal formula. Letter grade is just a bunch of ifs.
*    Then go through each variable and check if its valid.
* Output:
*    If there is an error, output an error message, if not, print the data.
* Assumptions:
*    It is assumed the inputs are doubles.
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  
  double a, b, c, d, e;
  //For sorting
  double temp;
  double average;
  char letterGrade;
  bool error = false;
  //INPUT
  
  cout << "Please Enter Five Test Scores." << endl;
  cin >> a >> b >> c >> d >> e;
  //Echo it back.
  cout << fixed << setprecision(2);
  cout << a << " " << b << " " << c << " " << d << " " << e << endl;

  //PROCESS

  //Same style sorting as last time.
  //You only need this for the median.
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

  //Now run through all variables,
  //Figure out min and max and look for error.
  //A
  if(a<0||a>100)
    error = true;
  //B
  if (b < 0 || b > 100)
    error = true;
  //C
  if (c < 0 || c > 100)
    error = true;
  //D
  if (d < 0 || d > 100)
    error = true;
  //E
  if (e < 0 || e > 100)
    error = true;

  //Set the average and get the grade;
  average = (a + b + c + d + e) / 5;
  if(average>=89.5)
    letterGrade = 'A';
  else if(average<89.5&&average>=79.5)
    letterGrade = 'B';
  else if(average<79.5&&average>=69.5)
    letterGrade = 'C';
  else if(average<69.5&&average>=59.5)
    letterGrade = 'D';
  else
    letterGrade = 'F';

  //OUTPUT
  if(!error){
    cout << endl;
    cout << "Average = " << average << endl;
    cout << "Grade   = " << letterGrade << endl;
    cout << "Min     = " << e << endl;
    cout << "Max     = " << a << endl;
    cout << "Median  = " << c << endl;
  }
  else {
    cout << "ERROR: BAD DATA" << endl;
  }
  return 0;
}