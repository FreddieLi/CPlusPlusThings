#include <iostream>
using namespace std;


class Apple {
public:
  Apple(int i):x(i){};
  const int ap = 7; /* C++11 and later version, we can assign value to const variable in class directly, no need to use member initializer list */
  int x;
  static const int apple_number;
  void take(int num) const {
    cout << "const take" << endl;
  };
  void take(int num) {
    cout << "non const take" << endl;
  };
  int add(int num){
    cout << "non const add" << endl;
    cout << "\t";
    x = 5; /* non const member function can read const/nonconst variable, can only modify nonconst variables.*/
    take(5);
    return 0;
  }
  int add(int num) const {
    cout << "const add" << endl;
    cout << "\t";
    cout << ap << x << endl; /* const member function can read const/nonconst variables, but can't write nonconst/const variables */
    take(5);
    return 0;
  }
  int getCount() const;
};

/* */
const int Apple::apple_number = 5;

main()
{
  Apple a(2);
  a.add(1);
  const Apple ca(2);
  ca.add(1);
  // call int add(int num) over int add(int num) const;
  // cout << a.ap << endl;
  // a.add(10); 
  // const Apple b(3);  // const instance can only call const member function. 
  // b.add(100); // only can call int add(int num) const;

}