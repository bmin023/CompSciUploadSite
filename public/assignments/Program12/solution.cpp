/*
* Author: Brendon Kofink
* Assignment Title:  Program 12
* Assignment Description: Given a data in various files, read them and output
*  each student's class average.
* Due Date: 10/1/2021
* Date Created: 09/28/2021
* Date Last Modified: 09/28/2021
*/

/*
* Data Abstraction:
*    Two input files. One for names, one for student data.
*    Doubles and ints to keep track of averages. Class average is initialized
*    to zero as it is persistent. Two doubles to keep track of min and max,
*    Two doubles to hold the final averages.
* Input:
*    Ask nicely for the name of the name file.
* Process:
*    Check if that was a file, if not, print and error. If it is, go through
*    the file, get each name and check if there's a related dat file.
*    If not, error. If empty, error. If there's data, read it and calculate
*    the average. Also add it to the overall sum to calculate average last.
* Output:
*    In process (we're stilled mixed), output a chart of the names next to
*    their grades or errors. At the end, output class average, min, and max.
* Assumptions:
*    It is assumed each dat file only has doubles.
*    It is assumed the name file has each line formatted LAST FIRST INITIAL.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION

  ifstream nameFile, dataFile;
  string filename;

  string first, last, initial;

  double classSum = 0;
  double studentSum;
  int classCount = 0;
  int studentCount;

  double currentGrade;

  double studentAverage, classAverage;

  double min, max;

  bool goodFile = true;

  //INPUT
  cout << "Enter Name of Data File: ";
  cin >> filename;
  cout << filename << endl;
  nameFile.open(filename);

  //PROCESS

  if (nameFile)
  {
    cout << endl;
    //Header
    cout << fixed << setprecision(2);
    cout << setw(25) << left << "Student" << setw(12) << left << "Average";
    cout << endl;

    //Go through the name file, returning each name.
    while (nameFile >> last >> first >> initial)
    {

      //Work setw is weird. So is left.
      cout << setw(25) << left << first + " " + initial + " " + last;
      cout << setw(12) << left;

      dataFile.open(first + last + ".dat");
      if (dataFile)
      {

        //Only the student count and sum reset.
        studentCount = 0;
        studentSum = 0;

        while (dataFile >> currentGrade)
        {

          //Add to both sums and counts.
          studentCount++;
          studentSum += currentGrade;
          classSum += currentGrade;
          classCount++;

          //Check for min and max.
          //If first number not set, init both min and max.
          if (classCount==1)
          {
            min = currentGrade;
            max = currentGrade;
          }
          if (currentGrade > max)
          {
            max = currentGrade;
          }
          if (currentGrade < min)
          {
            min = currentGrade;
          }
        }
        //Check if there were any grades.
        if (studentCount > 0)
        {
          studentAverage = studentSum / studentCount;
          cout << studentAverage << endl;
        }
        else
        {
          cout << "No Grades" << endl;
        }
      }
      else
      {
        //Data file didn't open.
        cout << "No Data File" << endl;
      }
      dataFile.close();
    }
  }
  else
  {
    //Name file didn't open
    cout << "ERROR : File Not Open." << endl;
    goodFile = false;
  }
  nameFile.close();

  //Calculate Average
  classAverage = classSum / classCount;

  //OUTPUT
  if (goodFile)
  {
    cout << endl;
    cout << "Class Average: " << classAverage << endl;
    cout << "Max Score: " << max << endl;
    cout << "Min Score: " << min << endl;
  }

  return 0;
}