class Implement{
  Implement(const Implement&);             // no copy
  Implement &operator =(const Implement&); // no copy
  protected:
  /**
   * size_t = sizeof(Implement)
   * 'operator new' and 'operator delete' are SMF(not ptr this)
   */
  void *operator new(size_t)throw(){} //disable: Implement *i=new Implement();
      
  void *operator new[](size_t respirate){
    return ::new(respirate);  // call global new()
  }
  void operator delete(void *){}        // disable: delete i;
  void operator delete[](void* respire) throw(){
      ::delete(respire);
  }
  
  ~Implement();  // disable: delete i;   delete'll call distruct func 
  public:
  /**
   * Covariant Return Type (Prototype)
   * what if rtn 'B*' or 'B&' in base class, derived class can rtn 
      'D*' or 'D&' instead
   * * virutal and friend are exclusion
   *      virtual friend int exclude() = 0;  // Error:
   *      B{virtual void exclude()=0;} D{friend void exclude(){}}  // Error:
   */
  virtual Implement *clone() const = 0;   // 'B *'
  virtual int rear() = 0;
};
class Heritor : public Implement{
  public:
  /**
   * Implement * Implement::clone()
      static_cast<Implement>Heritor
   */
  Heritor *clone() const;                 // 'D *' to 'B *' covariant
  int rear(){return 100;}
};





/**
 * DerivedClass: public B1Class ==>
 * DerivedClass: private B1Class ==> public/protected/private turns to private
 * DerivedClass: protected B1Class ==> public/protected turns to protected
 */

class Recollect{
  private:
    int x;
  public:
    Recollect(){cout << "Recollect::Recollect()" << endl;}
    Recollect(int j){
      x=j;
      cout << "Recoolect::Recollect(int) :" << j << endl;
    }
    virtual Blackout *insomnia() const = 0; // Factory Method
    void setX(int i):x(i){}
    void getX(){return x;}
    bool checkX(int y){return x == y;}
};
 
 
class Remembrance : private Recollect,    // private inherit
                    protected std::string, 
                    private std::valarray<int>
{
    private:
    public:
        Remebrance(){cout << "Remembrance::Remembrance()" << endl;}
        Remebrance(int j): Recollect(j){}  // set its parent's construct
        Recollect::setX;    // turn private public
        Recollect::getX;
};

void recall(Recollect r){
    cout << r.getX() << endl;
}

/**
 
  Remebrance -[INHERITE]-> Recollect
  Recollect::Recollect() --> Remembrance::Remembrance()
  --> Remembrance::~Remembrance() --> Recollect::~Recollect()
 
 
 */
Remembrance r;
r.setX(100);  // ok
r.getX(); // 100
// r.checkX(100)   false,  it's a private method
 
/**
 *
 */
Remebrance r2(100);
recall(r2);
 
 
/**
 * static, inline and construct function can't be a virtual function
 * destruct function can be a virtual function
 
 * compare in ptr
 */ 
 

class B{
    public:
    const char *polymer;
    B(const char *p="p-B"):polymer(p){}
    void polymorphism(){
        cout << "p()-B" << endl;
    }
    virtual void polymorphism(const char *p){
        cout << "p(\"" << p << "\")-B" << endl;
    }
    virtual ~B(){}
};

class Bin{};
class D: public B, public Bin{
    public:
    D(const char*p = "p-D"):polymer(p){}
    void polymorphism(){
        cout << "p()-D" << endl;
    }
    virtual void polymorphism(const char *P){
        cout << "p(\"" << p << "\")-D" << endl;
    }
    virtual ~D(){delete polymer;}
} 
                    
/*************************** Base = Derived ***********************************/
D d;
/*1*/     B b = * dynamic_cast<B *>(&d);

/*2*/     B b = d;
// derived = b1;  ERROR!!!
/************************  Base points to Derived  ****************************/
D d;
/*1*/     B* b_p = new D();
/*2*/     B* b_p = dynamic_cast<B *>(&d);
/*3*/      B* b_p = &derived;   
/************************  B=D, B ****************************/
b.polymorphism();           b_p->polymorphism();            // p()-B
b.polymorphism("Lef");     b_p->polymorphism("Lef");        // p("Lef")-D


/*************************  Derived points to B1  *****************************/
B b;
/*1*/    D d = * static_cast<D *>(&b);
/*1*/     D* d_p = static_cast<D *>(&b);
/*2*/     D* d_p = &b;
/*3*/    D* d_p = new B();
d.polymorphism();    d_p->polymorphism();                // p()->D
d_p->polymorphism("Lef");                                // p("Lef")-D

/******************************  ptr compare  *********************************/
D *derivation = new D();
/**
 * blab = derivation + ΔD_B;   deltaD_B: B's offset in D
 */
B *blab = derivation;
/**
 * blister = derivation + ΔD_Bin;   deltaD_Bin: Bin's offset in D
 */
Bin *blister = derivation;
        ----|--D--| <--------   derivation ptr to the addr. of the D() in heap
         |  |     | ΔD_B, may be zero
     ΔD_Bin |-----| <--------   blab ptr to here in heap of derivation
         |  |  B  |
        ----|-----| <--------   blister
            | Bin |
            |-----|
derivation == blab    // derivation turns to blab's base class's 'B' object place
blister == derivation
blab != blister      // blab = derivation + ΔD_B; blister = derivation + ΔD_Bin;
/**
 * blab is not derived from D any more
 * derivation  !=  (derivation + ΔD_B)
 */
derivation != reinterpret_cast<void *>blab;




class B{
    public:
    const char * homonym = "B";
};
class Ba: public B{
    public:
    const char * homonym = "Ba";
};
class Bb: public B{
    public:
    const char * homonym = "Bb";
};
class D: public Ba, public Bb{
    public:
    const char * homonym = "D";
    void parallel(){
        cout << Ba::homonym << endl;
        cout << Bb::homonym << endl;
        cout << this->homonym << endl;
    }
};

D d;
d.parallel();








