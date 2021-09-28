/*
* Author: Brendon Kofink
* Assignment Title:  Program Tem
* Assignment Description: Use Ceasar Cipher to encrypt and decrypt messages.
* Due Date: 09/24/2021
* Date Created: 09/15/2021
* Date Last Modified: 09/21/2021
*/

/*
* Data Abstraction:
*    Create variables for the files, input, and output.
*    Also make booleans for remembering if there are errors.
*    Keep an integer for each vowel to keep track of count.
* Input:
*    Ask for the file to convert as well as what method to use for the cipher.
* Process:
*    Make sure there are no errors in the input, then go 
*    character by character, convert it and add it to the output.
*    If its a vowel, add to that vowel's count.
*    If its a newline, leave it be.
* Output:
*    If no errors:
*      Output the message, upload it to a file, and give frequence of vowels.
*    If errors:
*      Print the errors.
* Assumptions:
*    It is assumed the file name has no spaces.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION

  //Files
  string fileName;
  ifstream input;
  ofstream output;

  //Strings
  string message = "";
  string line;
  string command;

  bool encrypt;
  char currentChar;

  //Letters
  int numA = 0;
  int numE = 0;
  int numI = 0;
  int numO = 0;
  int numU = 0;
  int numY = 0;

  //Errors
  bool badFile;
  bool badCommand;

  //INPUT

  cout << "Enter File Name: ";
  cin >> fileName;
  cout << fileName << endl; //Echo it back.
  cout << "Enter encrypt or decrypt: ";
  cin >> command;
  cout << command << endl; //Echo it back.

  //PROCESS (a little input)

  input.open(fileName);

  //Check if there are errors.
  badFile = !input;
  badCommand = !(command == "encrypt" || command == "decrypt");
  if (!badFile && !badCommand)
  {

    encrypt = command == "encrypt";

    //Loop. Read a line, convert it, add it to the message.
    while (input.get(currentChar))
    {
      //Check for vowels.
      if (tolower(currentChar) == 'a')
      {
        numA++;
      }
      else if (tolower(currentChar) == 'e')
      {
        numE++;
      }
      else if (tolower(currentChar) == 'i')
      {
        numI++;
      }
      else if (tolower(currentChar) == 'o')
      {
        numO++;
      }
      else if (tolower(currentChar) == 'u')
      {
        numU++;
      }
      else if (tolower(currentChar) == 'y')
      {
        numY++;
      }

      //Respect the newline.
      if(currentChar!='\n') { 
        //Shift right or left depending on the method.
        message += currentChar + (encrypt ? 3 : -3);
      }
      else {
        message += '\n';
      }
    }
  }

  input.close();

  //OUTPUT
  output.open("message");

  if (!badFile && !badCommand)
  {
    cout << endl << message << endl << endl; //Send to screen.
    output << message; //Send to file

    //Letters
    cout << "Letter Frequency" << endl;
    cout << setw(4) << "A" << setw(7) << numA << endl;
    cout << setw(4) << "E" << setw(7) << numE << endl;
    cout << setw(4) << "I" << setw(7) << numI << endl;
    cout << setw(4) << "O" << setw(7) << numO << endl;
    cout << setw(4) << "U" << setw(7) << numU << endl;
    cout << setw(4) << "Y" << setw(7) << numY << endl;
  }
  else
  {
    if (badCommand)
    {
      cout << "Error: Bad Command." << endl;
    }
    if (badFile)
    {
      cout << "Error: File did NOT open." << endl;
    }
  }

  output.close();

  return 0;
}