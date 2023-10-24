#include <iostream>
using namespace std;

/* friend keyword doing two things,
1. seem like it make the function inside class as a global funciton. Not a memeber function.
2. Allow this global function to access private/protected memeber. */
class TwoDimension {
public:
  double r, i;

public:
  TwoDimension(double R = 0, double I = 0) : r(R), i(I){};
  friend TwoDimension operator+(TwoDimension a, TwoDimension b);
/* okay, implemented as memeber function */
// bool operator==(TwoDimension &a)
// {
//     return (r == a.r && i == a.i) ? true : false;
// }

// Error!! Too many arguments. Should move it to outside
// bool operator==(TwoDimension &a,TwoDimension &b) 
// {
//     return (b.r == a.r && b.i == a.i) ? true : false;
// }
/* With friend keyword, seem like this function is treated as global function. 
!!! Not a member function!!! That's why this function can take 2 arguments. */
// friend bool operator==(TwoDimension &a, TwoDimension &b)
// {
//     return (b.r == a.r && b.i == a.i) ? true : false;
// }

  friend TwoDimension operator+(TwoDimension a, double b) {
    cout << "operator+(TwoDimension a, double b)" << endl;
    return TwoDimension(a.r + b, a.i);
  }
  friend TwoDimension operator+(double a, TwoDimension b) {
    cout << "operator+(double a, TwoDimension b)" << endl;
    return TwoDimension(a + b.r, b.i);
  }

  void display();
};

bool operator==(TwoDimension &a,TwoDimension &b)
{
    return (b.r == a.r && b.i == a.i) ? true : false;
}

TwoDimension operator+(TwoDimension a, TwoDimension b) {
  cout << "operator+(TwoDimension a, TwoDimension b)" << endl;
  return TwoDimension(a.r + b.r, a.i + b.i);
}

void TwoDimension::display() {
  std::cout << r;
  if (i > 0)
    std::cout << "+";
  if (i != 0)
    std::cout << i << "i" << std::endl;
}
int main(void) {
  TwoDimension c1(1, 2), c2(1, 2), c3, c4, c5, c6;
  TwoDimension a, b(2, 3);
  TwoDimension a1 = b + 2;
  TwoDimension a2 = 2 + b;
  a1.display();
  a2.display();
  c3 = c1 + c2;
  cout << ((c1==c2) ? "TRUE" : "FALSE") << endl;
  
  return 0;
}
