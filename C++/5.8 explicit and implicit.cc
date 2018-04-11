class Sediment{
    public:
    Sediment(int n);    // implicit and explicit are both allowed
    operator int() const;  // covert int() operator to Sediment
    explicit Sediment(double n);    // explicit call only, Sediment::Sediment()
}

Sediment a = 10;  //implicit conversion, calls Sediment::Sediment(int)
Sediment b(10); //OK, calls Sediment::Sediment(int)
Sediment c = Sediment(10);  //OK, calls Sediment::Sediment(int)
Sediment d = (Sediment)10; // OK, calls Sediment::Sediment(int)

Sediment a;
int n = a;  // int-to-Sediment automatic conversion

Sediment p = 10.10;  // NOT allowed, Compile-time error: can't convert 10 to an object to type Scar

Sediment p(10.10);  // explicit conversion
Sediment q = Sediment(10.10);  // OK
Sediment r = (Sediment) 10.10; //OK, NOTICE !!!!!!!!!

class Scar{
    public:
    explicit Scar(int n);
}

Scar a = 10;  //Compile-time error: can't convert 10 to an object to type Scar
Scar b(10); //OK, calls Scar::Scar(10)
Scar c = Scar(10);  //OK, calls Scar::Scar(10)
Scar d = (Scar)10; // OK, calls Scar::Scar(10)



class Scathe{
    public:
    Scathe(double x);
    explicit Scathe(bool x);
}

Scathe a = true;  //OK, implicitly, calls Scathe::Scathe(double true)
Scathe b = Scathe(true); //OK, calls Scathe::Scathe(bool true)