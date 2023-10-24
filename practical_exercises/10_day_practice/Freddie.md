Key note for [operator_plus](day4/clock/operator_plus.cpp)
1. How to overload ++i and i++  

Key note for [member initializer list](day5/ctor_dtor/ctor_d.cpp)  
1. First will call ctor of basic class which is class C.
2. then init the memeber variable which are b, a, c.


Key note for [ctor order](day5/ctor_dtor/seq.cpp)  
1. Class D inherit Class B, if the B constructor is called in member initializer list, then ctor of B wont be called again.
2. pass 0 to ctor of a0, if a0 is not in member initializer list.
3. Since Class have ctor, compiler wont create default zero-parameter ctor.
4. The sequence is B(1) then c1,c2, then a1,then a0 a4. note that a0 is not in memeber initializer list, which imply the member variable memory allocation is earlier than memeber initializer list.

Key note for [ctor order with virtual inheritance](day5/virtual/seq.cpp)  
1. public B1 first, since B1 virtual inherit B and A, so the order is `B A B1`
2. then public B2, since B2 DID NOT virtual inherit A, so the order is `A B2`. because B2 virtual inherit B, and B's ctor is already called earlier.
3. After base class ctor are called, init member variable which is `A a`; then the last step is call drived class ctor. 


Key note for [ctor order with virtual inheritance](day6/virtual_func/vis.cpp)  
1. indirectly call virtual function.  

Key note for [operator overloading](day7/binary_operator/operator.cpp)  
1. Dont know why a = b + 2 is valid. 
[better solution is here](day7/binary_operator/friend_operator.cpp)  

