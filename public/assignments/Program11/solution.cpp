/*
* Author: Brendon Kofink
* Assignment Title:  Program 11
* Assignment Description: Given data from a gps, 
*  calculate the distance traveled, the average distance, 
*  and the final distance from start.
* Due Date: 09/29/2021
* Date Created: 09/23/2021
* Date Last Modified: 09/23/2021
*/

/*
* Data Abstraction:
*    Vairables to store various stages of x and y, 
*    one to hold the current command as well as a double for each output.
* Input:
*    Use an Input Validation Loop as specified and coded in assignment 9.
*    Ask for file name, check if its good, if not send an error code. Do while.
* Process:
*    First, get rid of all lines before the first START COMMAND.
*    Then loop until the first STOP command. Grab the command, x and y.
*    Add distances and increase a count variable to calculate it at the end.
* Output:
*    Final Location, Total distance traveled, Distance to starting point,
*    and Average distance to start point in that order
* Assumptions:
*    It is assumed the file has a STOP command.
*    It is assumed the file contains proper data. (string, double, double)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION
  string filename;
  ifstream input;

  string command;
  double x, y;
  double startX, startY;
  double prevX, prevY;
  double stopX, stopY;

  double totalDist = 0;
  double avgDistFromStart = 0;
  double distFromStart = 0;
  int count = 0;

  //INPUT

  //Input Validation Loop
  do
  {
    cout << "Please Enter The Name Of The Data File: ";
    cin >> filename;
    cout << filename << endl; //Echo it back.
    input.open(filename);
    if (!input)
    {
      cout << "Error: File failed to open." << endl;
    }
  } while (!input);
  
  //PROCESS

  //Skip the first two lines of data.
  getline(input, command);
  getline(input, command);

  //Read trash data.
  do {
    input >> command >> x >> y;
  } while(command!="START");
  startX = x;
  startY = y;
  
  //Main loop.
  do {
    prevX = x;
    prevY = y;
    input >> command >> x >> y;
    totalDist += sqrt(pow(prevX - x, 2) + pow(prevY - y, 2));
    avgDistFromStart += sqrt(pow(startX - x, 2) + pow(startY - y, 2));
    count++;
  } while (command != "STOP");

  input.close();

  stopX = x;
  stopY = y;
  //Calculate average distance from start
  avgDistFromStart /= count;
  //Calculate start distance
  distFromStart = sqrt(pow(startX - stopX, 2) + pow(startY - stopY, 2));
  
  //OUTPUT

  cout << fixed << setprecision(1) << endl;
  cout << "Final Location: (" << stopX << ", " << stopY << ")" << endl;
  cout << "Total distance traveled " << totalDist << endl;
  cout << "Distance to starting point " << distFromStart << endl;
  cout << "Average distance to start point = " << avgDistFromStart << endl;

  return 0;
}