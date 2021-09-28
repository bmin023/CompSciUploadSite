/*
* Author: Brendon Kofink
* Assignment Title:  Program Seven
* Assignment Description: Make a console based guessing game.
* Due Date: 09/17/2021
* Date Created: 09/09/2021
* Date Last Modified: 09/09/2021
*/

/*
* Data Abstraction:
*    5 ints, keeping track of inputs as well as our random number and tries.
* Input:
*    In my currecnt implementation, input is necessarily mixed up with process.
*    But first, get the min max making sure to echo print.
* Process:
*    Create a game loop that only terminates when the guess is correct. It:
*        Gets a guess from the user.
*        Checks the guess for if its too low or high, outputs that.
* Output:
*    Again, pretty mixed with process. But output the amount of tries.
* Assumptions:
*    It is assumed the user gives valid arguments for all inputs.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  //DATA ABSTRACTION

  int randNum;
  int guess;
  int min, max;
  int tries = 0;
  int temp;

  //INPUT

  cout << "Please enter 2 integers: ";
  cin >> min >> max;
  cout << min << " " << max << endl
       << endl; //Echo it back

  //PROCESS and More INPUT and OUTPUT

  //Seed the rand function right at the beginning.
  srand(time(0));

  //Make sure the min is actually the min.
  if (min > max)
  {
    temp = min;
    min = max;
    max = temp;
  }

  randNum = (rand() % (max - min + 1)) + min;
  cout << "I'm thinking of a number between " << min << " and " << max << "."
       << endl << endl;

  //Game Loop
  do
  {
    //Get a guess
    cout << "Enter guess: ";
    cin >> guess;
    cout << guess; //Echo it back
    if (guess < randNum)
    {
      cout << " - Too Low";
    }
    else if (guess > randNum)
    {
      cout << " - Too High";
    }
    tries++;
    cout << endl
         << endl;
  } while (guess != randNum);

  //OUTPUT

  cout << "Correct, it took you " << tries << " tries to guess my number.";

  return 0;
}