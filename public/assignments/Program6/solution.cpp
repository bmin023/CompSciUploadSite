/*
* Author: Brendon Kofink
* Assignment Title:  Program Six
* Assignment Description: 
*  Output the roots if a quadratic equation given its three coefficients. 
* Due Date: 09/10/2021
* Date Created: 09/04/2021
* Date Last Modified: 09/07/2021
*/
/*
* Data Abstraction:
*    Three double, a,b,c for inputs.
*    A bool to decide if there's roots, two doubles for roots,
*    and a double for the discriminator.
*    Two doubles for saving the vertex x and y.
* Input:
*    Grab all three inputs and assign them to a,b, and c.
* Process:
*    First check if there's roots by checking if the discriminator < 0.
*    If it's == 0 then there's one root. Then get the roots with the normal
*    formula. One for plus and one for minus.
*    The vertex is -b/2a for x and plug that in for y.
* Output:
*    Output one or two roots, depending if they're the same or not.
*    If there are no roots, print "NO REAL ROOTS"
*    Output the vertex.
* Assumptions:
*    It is assumed the user inputs valid arguments.
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  //DATA ABSTRACTION

  double a, b, c;
  double root1, root2;
  double discriminant;
  bool hasRoots;
  bool twoRoots;
  //Vertex x and y.
  double x, y;

  //INPUT

  cin >> a >> b >> c;

  //PROCESS

  discriminant = b * b - (4.0 * a * c);
  hasRoots = discriminant >= 0;

  //roots
  if (hasRoots)
  {
    root1 = (-b - sqrt(discriminant)) / (2 * a);
    root2 = (-b + sqrt(discriminant)) / (2 * a);
  }

  //There's a funny problem where root1 can be -0.00.
  //I'll just set it to normal 0.00
  if (fabs(root1) < 0.0001)
  {
    root1 = 0.0;
  }

  //vertex
  x = -b / (2 * a);
  y = a * x * x + b * x + c;

  //Same zero problem with x.
  if (fabs(x) < 0.0001)
  {
    x = 0.0;
  }
  twoRoots = discriminant > 0;

  //OUTPUT

  cout << fixed << setprecision(2);
  //Check if it has roots first.
  if (hasRoots)
  {
    cout << root1 << " ";
    //only print the second root is it's unique.
    if (twoRoots)
    {
      cout << root2 << " ";
    }
  }
  else
  {
    //If no roots,
    cout << "NO REAL ROOTS ";
  }
  //Now print vertex.
  cout << "(" << x << "," << y << ")";
  return 0;
}