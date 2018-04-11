/**
 * Static Member functions (SMF): can't use 'inline'
    - SMFs are not attached to an object, they have no 'Cls *const this' ptr!
    - SMFs are all pointers just like common functions!
    - 'operator new' and 'operator delete' are all SMF !
    e.g. 
        int (*dejection)(int) = Faecal::excrement;
        int (*dejection)(int) = &Faecal::excrement;  // same as above
        dejection(100);
        (*dejection)(100);  // same as above
        
 * Non-static Member functions (functor: Function Objects)
    - functors are not pointers, because they hold 'Cls *const this [const]' ptr, and function in Cls
    e.g. 
        int (Faecal::*soil) ()= &Faecal::shitty;  // & is necessary
        Faecal faecal;
        (faecal.*soil)();  // a functor ptr in Faecal, "faecal.*" is necessary
    - A ptr to a derived class's functor can points to its base class's functor, but converse is wrong (not vice versa)
    e.g.
        T (Derived::*d_nsmf)(T-types) = &Base::nsmf;  // it works
        T (Base::*b_nsmf)(T-types) = &Derived::nsfm; // Error
        
 * '->*' and '.*' 
    - are the offset to a functor in a class ptr, but not ptr themselves
    - have lower priority than '()', so 
        (cls.*functor)() 
        (cls_ptr->*functor)()
 */
class Faecal {
    static int faeces;
    public:
    static int defacate;
    static int excrement(int pee) { 
        return faeces + pee; 
    }
    int dropping(int piss, int urine) const {
        return excrement(piss) + urine;
    }
};
int Faecal::faeces = 100; // initialize a private, it can't be using in main() {}
int Faecal::defacate = 200;
int main(int argc, char * argv[]) {
    /**
     * SMF such as common function are pointers
     *  int (*dung)() = &Faecal::excrement = Faecal::excrement;
        dung() = (*dung)()
     */
    int (*dung)(int) = Faecal::excrement; // SMF is a pointer like common function
    printf("%d", dung(25));  // 125
    /**
     * functor holds 'Cls *const excremental', it's not a pointer
     */
    int (Faecal::*stool)(int,int) const = &Faecal::dropping;  // & is necessary
    Faecal faecal;
    printf("%d", (faecal.*stool)(0,0));  // 100, it's not a pointer
} 
 

/**
 *  "T *"           to "const T *"      bingo
    "T **"          to "const T **"     Error
    "derivedCls *"  to "baseCls *"      bingo
    "derivedCls **" to "baseCls **"     Error
 */
Anaemia *anaemia =  new Anaemia("piss");    //call Anaemia::Anaemia(const char*)
Disease *disease = static_cast<Disease *>(anaemia); // Disease *disease=anaemia;
Anaemia **anaemic = &anaemia;   // it works
Disease **diseased = anaemic;   // ERROR

const Anaemia *starve = new Anaemia;        // call Anaemia::Anaemia()
Disease *pathogenic = static_cast<Disease *>(const_cast<Anaemia *>(starve));

Disease *pathogeny = new Disease;
const Disease *illness = pathogeny;
Anaemia *hypoxia = dynamic_cast<Disease *>(pathogeny);
const Anaemia &dizzy = dynamic_cast<const Anaemia &>(*pathogeny);
Anaemia &nausea = dynamic_cast<Anaemia &>(*const_cast<Anaemia *>(illness));


/**
 * pointer 'this' in a class is type of 'Cls *const', a const pointer that 
    points to this class.
   Using "const" to modify pointer "this" to "const Cls *const"
   'mutable' indicates it can be mutable for 'const Cls *const this'
   'constructors' may not be cv-qualified(const/volatile)
 */
template <class TC, typename T>
class Insomnia: public Desease {
    public:
    TC &unrelatedClass;
    T (TC::*couch)(T, T) const;
    mutable float amnesiac;
    float amnesia;
    
    /**
     *  Insomnia *const this
        Insomnia::Insomnia can't use cv(const/volatile)
     */     
    explicit Insomina(float blackout): amnesia(blackout) {}
    Insomnia(int oblivious): amnesiac:(oblivious) {}
    
    Insomnia(TC &c, T (TC::*nsmf)(T, T) const): unrelatedClass(c), couch(nsmf) {}
    T operator [](T yam, T doze) {
        return (unrelatedClass.*couch)(yam, doze);
    }
    
    
    
    // 'Insomnia *const this' to 'const Insomnia *const this'
    Insomnia * slumber(float memory_loss) const {
        amnesia = memory_loss; // Err: a 'const this' pointers to 'const Insmonia'
        amnesiac = memory_loss; // mutable
        Insomnia *const anomalousInsomnia = const_cast<Insomnia *const>(this);
        anomalousInsomnia->amnesia = memory_lose; // it's anomalous
        return this;
    }
    Insomnia * slumber(float memory_loss) {
        amnesia = memory_loss;
        return this;
    }
    Insomnia &operator ()(float unlearn) {
        amnesia = unlearn;
        return *this;
    }
    const Insomnia &operator ()(float unlearn) const {
        amnesiac = unlearn;
        return *this;   // 'Insomnia' to 'const Insomnia'
    }
    
};

Insomnia insomnia = 10;         // explicit -> amnesia = 10.0
const Insomnia oblivion(10);    // int      -> amesiac = 10
insomnia.slumber(10.0);     // Insomnia *const this;   amnesia = 10.0
oblivion.slumber(10.0);     // const Insomnia *const this; mutable amnesiac=10.0
insomnia(10.0);
oblivion(10.0);

Faecal faecal;
Insomnia<Faecal, int> drowse(&faecal, &Faecal::dropping);
drowse[0,0];  // 100,  excrement(0) + 0

