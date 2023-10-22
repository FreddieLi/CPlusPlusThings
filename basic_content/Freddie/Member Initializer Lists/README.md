C++对象初始化成员变量，推荐用初始化列表这种语法来实现。对于const修饰的成员变量，以及没有定义zero-parameter constructor的class type成员变量，只能用这种方式初始化，在初始化列表中调用基类的构造函数比较自然。

```cpp
#include <iostream>
using namespace std;

class xyz{
    int a;
    int b;
    const int c;
public:
    xyz(int a, int b, int c);
    xyz(int b1, int c1);
    xyz(int c);
};

xyz::xyz(int a, int b, int c):
    a(a),
    b(b),
    c(c) {
    cout << this->a << " " << this->b << " " << this->c << endl;
}

xyz::xyz(int b1, int c1):
    a{123},
    b{b1},
    c{c1} {
    // a = 123;  // initialized above with a constant
    cout << a << " " << b << " " << c << endl;
}

xyz::xyz(int c):
    c(c) {
    a = 11;
    b = 22;  // not recommended
    cout << a << " " << b << " " << this->c << endl;
}

int main(void) {
    xyz x(1,2,3);
    xyz y(234,345);
    xyz z(33);
    return 0;
}
```

如果不在初始化列表中初始化const int c这个成员，编译器会报错！

创建一个对象，首先准备好内存，然后执行constructor，initialization list出现在这两者之间，如const变量，如果在constructor内赋值，感觉就有点不对了，似乎就不具有constness属性。initialization list只是初始化members，constructor内可以干很多其它的事情。

初始化列表可以用于全部成员变量，也可以只用于部分成员变量。初始化列表只能出现在构造函数的实现上，而且在构造函数体执行之前完成执行。

上面的代码，初始化列表有的用圆括号，但更应该使用大括号{}！C++把所有的这些基础类型也看成对象，建议统一使用{}来初始化，下面有一个在初始化列表中初始化数组的示例，就只能使用大括号。不推荐使用()的原因，它看起来很像function call！容易让人疑惑...而且不能检查narrow conversion。

`a{}，表示将a初始化为0。`  

如果申明时定义了const int c {1};，1这个值会在初始化列表中被新的值覆盖。合法的初始化可以覆盖预先定义的const变量的值！（const成员的值，可在定义时指定，可在初始化列表中指定，后者会覆盖前者，但就是不能在ctor中显示赋值）

在使用初始化列表的方式初始化成员变量时，允许构造函数的入参的名称与成员变量名称一样，他们分别在大括号内或外，不会有歧义。而在其它函数内部代码中，如果入参与成员变量名称相同，区分成员还是入参，就要使用this指针。


为什么要设计初始化列表？
初始化列表，英文叫做 Member Initializer Lists，注意是member。

它可初始化所有的class members；
它在构造函数被调用之前就会完成执行（在对象内存准备好了之后）。
在一本C++教材中，提到了这种设计的好处：

确保在构造函数执行之前，所有成员已经完成初始化，因此你可以更加专注于构造函数的内部逻辑，不用考虑初始化成员变量的问题。（言下之意，初始化member不应该属于ctor）
我觉得还有更重要的原因：

const成员的初始化，如果放在构造函数中，会有些怪异，比如const变量不应该出现显式地赋值操作。
在初始化列表中，可以自然地调用基类的构造函数，将初始值传入，初始化从基类中继承下来的那些变量。在函数体中使用基类的构造函数，就不是初始化了，而是创建一个基类对象。（详见详解C++中的继承），测试代码：

```cpp
#include <iostream>
using namespace std;

struct bob{
    int a;
    const int c = 1;
    bob(int a): a{a} {}
};

struct tom: bob{
    int d;
    tom(int a, int d):
        bob{a}, d{d} {} // bob{a} first
};

int main(void) {
    tom t{3,5};
    cout << t.a << " " << t.c << " " << t.d << endl;
    return 0;
}
```

如果某个成员变量是class type，而且这个type没有定义zero-parameter constructor，它也只能在initialization list中完成初始化。有zero-parameter constructor，只是隐式地被默认调用进行初始化。示例：
```cpp
#include <iostream>
using namespace std;

struct bob{
    int a;
    const int c;
    bob(int a, int c): a{a},c{c} {}
};

struct tom{
    bob b;
    int d;
    tom(int a, int c, int d):
        b{a,c}, d{d} {}
    tom(int d): d{d} {} // call bob's zero-parameter constructor
};

int main(void) {
    tom t{7,3,5};
    cout << t.d << " " << t.b.a << " " << t.b.c << endl;
    //tom t3{7};  // compile error, bob has no zero-param constructor
    return 0;
}
```

初始化列表的顺序
初始化列表有个顺序问题，对象成员变量的初始化顺序是按照变量申明顺序（从上到下）进行的，如果有继承，基类排在前面。

请看下面代码：
```cpp
#include <iostream>
using namespace std;

class xyz{
    int a;
    int b;
    const int c;
public:
    xyz(int a1, int b1, int c1);
};

xyz::xyz(int a1, int b1, int c1):
    b{a1},
    a{b},
    c{c1} {
    cout << a << " " << b << " " << c << endl;
}

int main(void) {
    xyz x(1,2,3);
    return 0;
}
```
把初始化列表按顺序翻译过来，就是：
`b = a1;`
`a = b;`
`c = c1;`
但是，编译器不是这么干的，编译器会按照变量的申明顺序进行初始化赋值：
`a = b;`
`b = a1;`
`c = c1;`
这就导致在b还没有值的时候，用b的值去给a赋初值，a的值就随机了！上面代码执行结果如下；
`132654704 1 3`

打印出来的a，是个随机数，完全不对。

使用-Wall -Wextra编译时，这种情况会出现一个reorder warning！既然有个专门的warning，此时，我们就只能严格按照申明顺序来填写初始化列表。就算有继承关系，也要按照顺序来编写初始化列表：
```cpp
#include <cstdio>

class aa {
public:
    int va;
    aa(int a):
        va{a} {
    }
};

class bb: public aa {
public:
    int vb;
    bb(int a, int b):
        vb{b},   // reorder warning！But not a bug!
        aa{a} {
    }
};

int main(void) {
    bb b(12, 32);
    printf("%u %u\n", b.va, b.vb);
    return 0;
}
```
上面这段代码，也会出现reorder的告警，需要将vb{b}和aa{a}上下交换顺序，让基类的初始化在前，就OK了。

编译器按照申明顺序初始化成员，而不管初始化代码中的书写顺序，如果代码书写顺序与申明顺序不一致，会出现Warning，仅仅是个Warning，小心可能因为代码执行顺序与书写顺序不一致而导致的问题。在初始化列表中跳过某些成员也是OK的！