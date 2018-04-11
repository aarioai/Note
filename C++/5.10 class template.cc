/**
 * partial specialization
 */
template <typename T>
class Stealth<T *>{};
Stealth<const char *> steal;    // T is 'const char', partial specialization
Stealth<int> doGoodByStealth;   // T is 'int', explicit specialization
Stealth<char **> rob;           // T is 'char *', partial specialization
 
template <class C, typename T1, typename T2>
class Stash<C (*)(T1,T2)>{}; 



/**
 * explicit specialization (absolute specialization)
 */ 
template <typename T1, typename T2, int initial_preexist = 100>
class Precede
{
    private:
        static int preexist;
    public:
        T1 precedence(T1 x){return x;}
        void precedent(T2 z);
};

template <typename T1, typename T2, int initial_preexist>
int Precede<T1,T2,initial_preexist>::preexist = initial_preexist;    // initialize static preexist;

template <typename T1, typename T2, int initial_preexist>
void Precede<T1,T2,initial_preexist>::precedent(T2 z){
    cout << "precedent: " << z << endl;
}

template <typename T1, typename T2, int initial_preexist>
void convey(Precede<T1,T2,initial_preexist> p){
    cout << p.precedence(initial_preexist) << endl;
}


Precede<int, const char *, 400> p;
const char * precession = "Lef-Well";
p.precedent(precession);
convey(p);   // 400




template <class Type>
class Fossil
{
private:
    enum{ SIZE = 10 };
    int dinosaurs;
    Type * petrifactions;
    int top = 0;
public:
    explicit Fossil(int n = SIZE) :dinosaurs(n){
        petrifactions = new Type[n];
    }
    bool push(const Type &item){
        if (top < dinosaurs){
            petrifactions[top] = item;
            top++;
            return true;
        }
        else{
            return false;
        }
        
    }
    Type * get(){
        return petrifactions;
    }
    ~Fossil(){ delete[] petrifactions; }

};

int size = 2;
    Fossil<int> fs(size);
    fs.push(1);
    fs.push(5);
    int * arr1 = fs.get();
    for (int i = 0; i < size; i++){
        cout << arr1[i] << endl;
    }
    
    Fossil<char *> fs2(size);
    fs2.push("petrol");
    fs2.push("gasoline");
    
    
/*****************************************************************/
template <class T, int N>
class Adamant
{
private:
    T arr[N];  // T and N are all from template
public:
Adamant(){};
explicit Adamant(const T &v);
virtual T & operator[](int i);
virtual T operator[](int i) const;
}

template <class T, int N>
Adamant<T,N>::Adamant(const T &v){
    for(int i = 0; i < N; i++){
        arr[i] = v;
    }
}

template <class T, int N>
T & Adamant<T,N>::operator[](int i){
    if(i<0 || i >=n){
        std::cerr << i << " is out of range";
        std::exit(EXIT_FAILURE);
    }
    return arr[i];
}

template <class T, int N>
T Adamant<T,N>::operator[](int i) const{
    if(i<0 || i >=n){
        std::cerr << i << " is out of range";
        std::exit(EXIT_FAILURE);
    }
    return arr[i];
}


/*****************************************************************/

template <typename T>
class Arr{
private:
    T entry;
}

template <typename T>
class Stack{
private:
    Arr<T> arr;
}

Arr< Stack<int> > arr;




/* You should use templates if you need functions that apply the same algorithm to a variety of
types. If you aren’t concerned with backward compatibility and can put up with the effort of
typing a longer word, you can use the keyword "typename" rather than "class" when you
declare type parameters. */

template <typename T> void func(T &a);   // implicit instantiation


/* Originally,using implicit instantiation was the only way the compiler generated func-
tion definitions from templates,but now C++ allows for explicit instantiation.That means
you can instruct the compiler to create a particular instantiation—for example,
Swap<int>()—directly.The syntax is to declare the particular variety you want,using the
<>notation to indicate the type and prefixing the declaration with the keyword
template: */

template void Swap<int>(int, int);  // explicit instantiation
template <> void Swap<int>(int &, int &);  // explicit specialization
template <> void Swap(int &, int &);       // explicit specialization

/* The difference is that these last two declarations mean “Don’t use the Swap() template
to generate a function definition.Instead,use a separate,specialized function definition
explicitly defined for the int type.”These prototypes have to be coupled with their own
function definitions.The explicit specialization declaration has <> after the keyword tem-
plate,whereas the explicit instantiation omits the <>.

It is an error to try to use both an explicit instantiation and an explicit specia
same type(s) in the same file,or,more generally,the same translation unit. */

template <class T>
T Add(T a, T b)    // pass by value
{
return a + b;
}
...
int m = 6;
double x = 10.2;
cout << Add<double>(x, m) << endl;  // explicit instantiation

/* The template would fail to match the function call Add(x, m)because the te
expects both function arguments to be of the same type.But using Add<double>
forces the type doubleinstantiation,and the argument mis type cast to type doub
match the second parameter of the Add<double>(double, double)function. */


void Swap(T &a, T &b); 

/* This generates an explicit instantiation for type double.Unfortunately,in this case,the
code won’t work because the first formal parameter,being type double &,can’t refer to
the type int variable m.
Implicit instantiations,explicit instantiations,and explicit specializations collectively are
termed specializations.What they all have in common is that they represent a function defi-
nition that uses specific types rather than one that is a generic description.
The addition of the explicit instantiation led to the new syntax of using template and
template <>prefixes in declarations to distinguish between the explicit instantiation and
the explicit specialization.As in many other cases,the cost of doing more is more syntax
rules.The following fragment summarizes these concepts: */

