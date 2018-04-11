/**
 * Sequence to call BaseClass's construct/destruct function   *****************
 *  ?. Calls member variables' constructs before it's own construct
            class X{
                Y y;
                Z z;
            };
        ==>  Y::Y --> Z::Z --> X::X
        
    1. Calls virtual class
            class D: public B1, virtual public V1, public B3{
                D(int a, int b, int c):B3(c), B1(a), V1(b)
            }
        ==>  V1::V1 -> B1::B1  ->  B3::B3  D::D
    2. Calls default BaseClass's construct method first. If there are more than 
        one BaseClass, call them via the seq. of declared.
            class D: public Base1, public Base2{        // via here
                Derived(int x): Base2(x), Base1(x);     // not here
            };

    4. Calls Derived class's construct method
    6. destruct of 4   -->  if ? , destruct ? of 4
    7. destruct of 3   -->  if ? , destruct ? of 3
    8. destruct of 2   -->  if ? , destruct ? of 2
    9. destruct of 1   -->  if ? , destruct ? of 1
    Sumary:
        class B2{
            B9 b9;
        };
        class B5{
                B4 b4;
        };
        class D: public B1, virtual public B2, public B3{    // VIA HERE
                B5 b5;               // not declared in inheritance
            public:
                D(int i):B3(i+3), B1(i+1), B2(i+2){}        // NOT HERE
                ~D(){}
        };
        
        =======================================================================>
        B2         => B9::B9() --> B2::B2(i+2)
        B1->B3     => B1::B1(i+1) --> B3::B3(i+3)
        D[B5]    => B4::B4() --> B5::B5()
        D        => D::D(i)
        ~D      => D::~D()
        ~D[B5]  => B5::~B5() --> B4::~B4()
        ~B3->B1 => B3::~B3() --> B1::~B1()
        ~B2     => B2::~B2() --> B9::~B9()
 */

class Hypoxia{
    const char *oxygen;
    public:
    Hypoxia(const char*o):oxygen(o){
        cout << "Hypoxia from " << this->oxygen << endl;
    }
    virtual ~Hypoxia(){delete oxygen;cout << "~Hypoxia" << endl;}
};
class Exclusion{
    Hypoxia hypoxia("Exclusion");
    public:
    Exclusion(){
        
        cout << "Exclusion" << endl;
    }
    virtual ~Exclusion(){cout << "~Exclusion" << endl;}
};
class Delude{

    public:
    Delude(){cout << "Delude" << endl;}
    virtual ~Delude(){cout << "~Delude" << endl;}
};
class Delusion{

};
class Cough{

};
class Breakdown: public Cough, virtual public Delusion, virtual public Delude{

};
class Blackout: public Coma, virtual public Delusion, virtual public Delude {

};

class Anaemia:  public Blackout, protected Breakdown, virtual private Exclusion{
        
};
/*
 * Mark 
    *: inherit virtual base class
        *1:blackout
        *2:breakdown
    |: inherit base class
 *******************************************************************************
    Coma    Delusion               Delude     Cough
      |      *1 *2                  *1 *2       |         
        Blackout(1)    Exclusion    Breakdown(2)
            |                           |
                        Anaemia
 *******************************************************************************
 */

 
 
 
 