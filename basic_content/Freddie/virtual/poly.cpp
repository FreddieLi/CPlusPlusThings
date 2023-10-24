/* When virtual function(e.g. print) call any other functions(e.g. getSalary), 
those function will be virtual function call as well. */
#include <iostream>
#include <string>
using namespace std;
class Employee {
public:
  Employee(string Name, string id) : name(Name), Id(id) {}
  string getName() const { return name; } 
  string getID() const { return Id; }     
  float getSalary() const { return 0.0; } 
  virtual void print() const {            
    cout << "name: " << name << "\t\t id: " << Id << endl;
  }

private:
  string name;
  string Id;
};

class Manager : public Employee {
public:
  Manager(string Name, string id, int week) : Employee(Name, id) {
    WeeklySalary = week * 1000;
  }
  float getSalary() const { return WeeklySalary; }
  void print() const { 
    cout << "manager" << getName() << "\t\t id: " << getID()
         << "\t\t salary: " << getSalary() << endl;
  }

private:
  float WeeklySalary;
};


int main() {
  Manager m("wang", "11111111", 5);
  Employee *ptr = &m;
  ptr->print(); // polymorphism, print() will call getSalary in derived class.
  cout << "salary "<< ptr->getSalary() << endl; // will call getSalary() in base class. 
  return 0;
}
