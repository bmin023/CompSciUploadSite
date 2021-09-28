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
  cout << filename << endl
       << endl; //Echo it back.
  nameFile.open(filename);

  //PROCESS

  if (nameFile)
  {
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
  // nameFile.close();

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