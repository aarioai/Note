class Copper;  //forward declaration

class Brass{
private:
    Copper * copper;
    char * alloy = new char[20];
public:
    void forge(Copper & cp);
    friend istream & operator >>(istream & i_stream, Brass & brass);
    friend ostream & operator <<(ostream & o_stream, Brass & brass);
}

istream & Brass::operator >>(istream & i_stream, Brass & brass){
    i_stream >> brass.alloy;
    return i_stream;
}

ostream & Brass::operator <<(ostream & o_stream, Brass & brass){
    o_stream << brass.alloy;
    return o_stream;
}


class Copper{
private:
    void smelt(){cout << "private-smelt"<<endl;}
public:
    // friend class Brass;  // use every private method;
    friend void Brass::forge(Copper & cp);  // Only forge() can access
};

// it must decelerated behind Copper's declaration
void Brass::forge(Copper &cp){
    cp.smelt();
}
    

Brass brass;
Copper cp;
brass.forge(cp);

/*****************************************************************/
    

class Anamnesis;
class Probe{
    friend void sync(Anamnesis & a, const Probe & p);
    friend void sync(Probe & p, const Anamnesis & a);
}
class Anamnesis{
    friend void sync(Anamnesis & a, const Probe & p);
    friend void sync(Probe & p, const Anamnesis & a);
}

inline void sync(Anamnesis & a, const Probe & p){
}

inline void sync(Probe & p, const Anamnesis & a){
}

Anamnesis a;
Probe p;
sync(a, p);