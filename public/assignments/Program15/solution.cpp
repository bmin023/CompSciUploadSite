/*
* Author: Brendon Kofink
* Assignment Title:  Program 15
* Assignment Description: Given inputs, print out corresponding
* matrix array of size input*input.
* Due Date: 10/13/2021
* Date Created: 10/05/2021
* Date Last Modified: 10/05/2021
*/
/*
* Data Abstraction:
*   A two dimensional array to hold the output, a vector to hold the input. 
*   And an int to hold the current size. The array has to be of size 100*100
*   as that is what the website specifies.
* Input:
*    Recieve inputs until one is below 0 and add them to a vector..
* Process:
*    Loop through the vector.
*    Loop through rows and columns.
*    The value of that coordinate is the minimum of the x+1 and y+1
*    If it is on the upper dialognal,
*    n minus the maximum of x and y if its on the lower.
* Output:
*    Loop through the rows and columns and print each to the screen.
*    Making sure to leave space so double digits look nice.
* Assumptions:
*    It is assumed all inputs will be integers less than 101.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  int matrix[100][100];
  vector<int> input;
  //Size of the matrix.
  int n;
  int min;
  int max;

  //INPUT
  while (cin >> n && n > 0)
  {
    input.push_back(n);
  }
  //Loop through each input.
  for (unsigned int inputIndex = 0; inputIndex < input.size(); inputIndex++)
  {
    //PROCESS
    n = input.at(inputIndex);
    for (int y = 0; y < n; y++)
    {
      for (int x = 0; x < n; x++)
      {
        if(x>y) {
          max = x;
          min = y;
        }
        else {
          max = y;
          min = x;
        }
        if(x<n-y) {
          matrix[y][x] = min + 1;
        }
        else {
          matrix[y][x] = n - max;
        }
      }
    }
    //OUTPUT
    for (int y = 0; y < n; y++)
    {
      for (int x = 0; x < n; x++)
      {
        cout << setw(3) << matrix[y][x] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}