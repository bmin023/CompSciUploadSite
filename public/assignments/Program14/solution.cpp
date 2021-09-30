/*
* Author: Brendon Kofink
* Assignment Title:  Program 14
* Assignment Description: Given an array of integers, print them in reverse.
* Due Date: 10/07/2021
* Date Created: 09/30/2021
* Date Last Modified: 09/30/2021
*/

/*
* Data Abstraction:
*    An integer to hold the number of values
*    An array to hold the actual values.
* Input:
*    Get the number of values, then for each of those,
*    Grab one input and put it in the array.
* Process:
*    Calculate the min, max, sum, and duplicates
*    by going through the array. And going through the array again
*    to see if this item matches anything else.
* Output:
*    Output the array going forwards
*    Output the array going in reverse.
* Assumptions:
*    It is assumed only integers are used for inputs.
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  int numVals;
  int values[25];
  int min, max;
  int sum = 0;
  vector<int> duplicates;
  bool found; // for duplicates
  bool inDuplicates;

  //INPUT
  cout << "Input the number of elements to store in the array: ";
  cin >> numVals;
  cout << numVals << endl; //Echo it back.

  cout << "Input " << numVals << " integers:" << endl;
  for (int i = 0; i < numVals; i++)
  {
    cout << "integer - " << i << " : ";
    cin >> values[i];
    cout << values[i] << endl; //Echo it back.
  }

  //PROCESS
  //Initialize min and max.
  min = values[0];
  max = values[0];

  //Find min, max, sum, and whatnot.
  for (int i = 0; i < numVals; i++)
  {
    if (values[i] < min)
    {
      min = values[i];
    }
    else if (values[i] > max)
    {
      max = values[i];
    }
    sum += values[i];
    found = false;
    {
      //Go through the array again, seeing is this value is in there.
      for (int j = i+1; j < numVals; j++)
      {
        if (!found && values[i] == values[j])
        {
          found = true;
          inDuplicates = false;
          //Go through the duplicates vector, see if its already there.
          for (unsigned int k = 0; k < duplicates.size(); k++)
          {
            if (!inDuplicates && values[i] == duplicates.at(k))
            {
              inDuplicates = true;
            }
          }
          //If not in duplicates, but in values, add to duplicates.
          if (!inDuplicates)
          {
            duplicates.push_back(values[i]);
          }
        }
      }
    }
  }

  //OUTPUT
  cout << endl << endl;
  cout << "The values stored into the array are :" << endl;
  for (int i = 0; i < numVals; i++)
  {
    cout << values[i] << " ";
  }
  cout << endl << endl;
  cout << "The values stored into the array in reverse are :" << endl;
  for (int i = numVals - 1; i >= 0; i--)
  {
    cout << values[i] << " ";
  }
  cout << endl << endl;
  cout << "The sum of all elements of the array is " << sum << endl;
  cout << "The total number of duplicate elements in the array is ";
  cout << duplicates.size() << endl;
  cout << "The maximum and minimum element in the array are ";
  cout << max << " , " << min << endl;
  return 0;
}