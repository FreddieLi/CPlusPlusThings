Key note for [operator_plus](day4/clock/operator_plus.cpp)
1. How to overload ++i and i++  

Key note for [member initializer list](day5/ctor_dtor/ctor_d.cpp)  
1. First will call ctor of basic class which is class C.
2. then init the memeber variable which are b, a, c.


Key note for [member initializer list](day5/ctor_dtor/seq.cpp)  
1. Class D inherit Class B, if the B constructor is called in member initializer list, then ctor of B wont be called again.
2. pass 0 to ctor of a0, if a0 is not in member initializer list.
3. Since Class have ctor, compiler wont create default zero-parameter ctor.
4. 