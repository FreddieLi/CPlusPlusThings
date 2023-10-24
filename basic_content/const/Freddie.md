1. non-const instance can call non-const member function and const member function. and will prioritize the non-const memeber function over const memeber function.
2. const member function can only call onther const member function, while non const member function can call other non-const member function(priortized) and const member.  
3. const member function can read const/nonconst variables, but can't write nonconst/const variables.
4. non const member function can read const/nonconst variable, can only modify nonconst variables.
5. C++11 and later version, we can assign value to const variable in class directly, no need to use member initializer list.  
```cpp
class a {
  public:
  const int constVar = 10;
}
```

```cpp
class Apple {
public:
  Apple(int i);
  static int ap;
  static const int apple_number;
  void take(int num) const;
  int add(int num);
  int add(int num) const;
  int getCount() const;
};

main()
{
  Apple a(2);
  // call int add(int num) over int add(int num) const;
  a.add(10); 
  const Apple b(3);  // const instance can only call const member function. 
  b.add(100); // only can call int add(int num) const;

}

```