/**
 * T (*[const] anomalous)(T-args)       a [const] ptr to T ()
   T (& unusual)(T-args)  // likes 'T (*const unusual)(T-args)'        
   T *(*mutate)(T-args)
   T (**[const] mutation)(T-args)   a [const] ptr that points to a ptr of T()
   T (*[const] muteness[N])()       an array with N elems. pointing to T ()
   T (*verbal()) <--> T (*)   a func rtn a ptr to T
   T (*dumb())[N] <--> T(*)[N]  a func rtn a ptr to T[N]
   T (*dumbbell())[N][N] <--> T(*)[N][N]   3D Array
   T (&oral())[N] <--> T (&)[N]  a func rtn a reference to T[N]
 */
 
/**
 * Difference between func-ptr and functor
 *  Common Func and Static Member Func are all Func-ptr
 *  Functor is a function object, not a ptr.
 *  Only Functors can be a 'inline' code, neither common function nor SMF;
 */
void (*facial)();   // a ptr to void(), not a func; so void(*f)() {...} is error
void cosmetics() {   // a function returns void
    printf("cosmetics");
};
extern void masquerade(int masque); // a function returns void
extern const int cosmetic();        // a function returns const int

/**
 * A func returns a ptr to void()
 * void (* ((*)()))()    --> raw is a func-ptr, ,so raw() ==>  (*)()
 */
void (*raw())() {
    printf("raw");
    return cosmetics;       // void()
}

void (* (*rawness)() )() = raw;   //  ()()  function

typedef void (*VoidFunc)();
VoidFunc raw() {
    printf("raw");
    return cosmetics;       // void()
}

VoidFunc (*rawness)() = raw;
VoidFunc diarrhoea = raw;
void (*   disrrhoea   )() = raw;
void (*  (*rawness)() )() = raw;



cosmetics();    // it works
(*cosmetics)(); // it works too 

raw();      // raw, it works
(*raw)();   // raw, works too
raw()();    // raw cosmetics

/**
 * Functions and Static Member Functions (SMF) are functions-pointers
    - T (*bud)() = func;   // compile coverts func to its addr. &func implicitly
      T (*bud)() = &func;  // assign explicitly
 */
facial = 0;  // correct, void (*facial)() = NULL;
facial = cosmetics; // OK, specify the addr. implicitly, compiler'll convert it
facial = &cosmetics; // OK, specify the function's addr. explicitly

facial = masquerade; // Error, 'void(*)()' to 'void(*)(int)'
facial = cosmetic;  // Error, 'void(*)()' to 'const int()'

(*facial)(); // call a ptr2func explicitly
facial();    // call a ptr2fun implicitly


void (**facePack)() =  &facial;
(**facePack)();

void (*mask[3])() = {facial, cosmetics, &cosmetics};//{facial,comestic,comestics}
(*mask[0])();   // facial() = (*facial)()
(**mask)();     // same as above
(**(mask+1))(); // cosmetics()

char (*cortex())[2] {    // char (*)[]
    char epidermis[3][2] = {86, 105, 110, 99, 101, '\0'};  // "Lef"
    char (*cortical)[2] = epidermis;
    return cortical;
}

char (*cuticle)[2] = cortex();

const char* (*dermis())[2] {     // const char* (*) []
    const char* derma[1][2] = {"Lef", "Well"};
    const char* (*corium)[2] = derma;
    return corium;
}

const char* (*dermic)[2] = dermis();



 /**
 * There's no "array argument" in C++, it'll be converted into "T *".
    T (&)[n] is an array arguments with n elements
    "char (&)[n]"  is different with "char *", though "char[n]" is "char *"
 */
void carbohydrate(char hydrate[5]) {  // convert to "char *"
    printf("%d: %s", sizeof(hydrate), hydrate); // 8 = sizeof(char *), not 20
}
void clayer(char (&clay)[5]) {
    printf("%d: %s", sizeof(clay), clay);    // 20
}
char dinosaur[5] = {'V','i','n','c','e'};
const char *dine = "Vinc";  // Vinc\0
const char *dint = "By dint of much trying he finally achieved his object.";
carbohydrate(dint);  // it works
clayer(dint); // ERROR: int(&)[5] to int[10]

void crafty(int (&craft)[3][2]) {
    int (*handcraft)[2] = craft;  // it works,  int *[2] to int *[2]
    int **handcraft = craft;      // Error: int *[2] to int **
}






char * revise(char * a, const char * b, char & c, char * d) {
    char * tmp = a;
    while( *a != '\0' && '\0' != (*a++ = *b++) );
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << c;
    c = 'K';
    cout << *d;    // K
    cout << "----------------------" << endl;
    char y = 'Y';
    d = &y;
    cout << c << "    " << *d;  // K    Y
    *d = y;
    cout << c << "    " << *d;  // Y    Y
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
    return tmp;
}

char amend[50] = "vince";


/*
 * now [ xerox = "vince" ]  [ *xerox = 'v' , the addr. of array "vince"] 
 */
char * xerox = amend;  // point to first member of array "vince" --> v
cout << xerox;  // vince
cout << *xerox++;   //  v ,  and after *xerox = 'i'
cout << *(xerox++);  // i, and after *xeorx = 'n'
*xerox++ = '-';     // make 'n' to '-', and *xerox = 'c'
cout << xerox;  // ce
cout << amend;  //vi-ce

cout << *xerox--;  // c
cout << *xerox;  // -



char * zit = (char *)malloc(strlen(amend) + 1);
// zit is allocated new memory addr.

const char * bane = "-Lef-Well-";
char cagy = 'C';
char *daemon = &cagy;


int len = strlen(revise(amend, bane, cagy, daemon));




cout << amend;  // -Lef-Well-
cout << cagy; // Y
cout << *daemon;  // Y
/*************************************************************************/



/* If and only if the argument is a constreference, C++ can generate a temporary variable if the actual argument doesn’t match a reference argument.

First,when is a temporary variable created? Provided that the reference parameter is a const,the compiler generates a temporary variable in two kinds of situations:
When the actual argument is the correct type but isn’t an lvalue
When the actual argument is of the wrong type,but it’s of a type that can be con-verted to the correct type. */

double refcube(const double &ra) {
    return ra * ra * ra;
}

double side = 3.0;
double * pd = &side;
double & rd = side;
long edge = 5L;
double lens[4] = { 2.0, 5.0, 10.0, 12.0};
double c1 = refcube(side);          // ra is side
double c2 = refcube(lens[2]);       // ra is lens[2] 
double c3 = refcube(rd);            // ra is rd is side
double c4 = refcube(*pd);           // ra is *pd is side
double c5 = refcube(edge);          // ra is temporary variable
double c6 = refcube(7.0);           // ra is temporary variable
double c7 = refcube(side + 10.0);   // ra is temporary variable

/* If a function call argument isn’t an lvalue or does not match the type of the corresponding
const reference parameter, C++ creates an anonymous variable of the correct type, assigns
the value of the function call argument to the anonymous variable, and has the parameter
refer to that variable.

Use const When You Can
There are three strong reasons to declare reference arguments as references to constant data:
nUsing const protects you against programming errors that inadvertently alter data.
nUsing const allows a function to process both const and non-const actual argu-
ments, whereas a function that omits const in the prototype only can accept non-
const data.
nUsing a const reference allows the function to generate and use a temporary variable
appropriately.
You should declare formal reference arguments as const whenever it’s appropriate to do so.

C++11 introduces a second kind of reference, called an rvalue reference, that can refer to
an rvalue. It’s declared using &&: */

double && rref = std::sqrt(36.00);  // not allowed for double &
double j = 15.0;
double && jref = 2.0* j + 18.5;     // not allowed for double &
std::cout << rref << '\n';          // display 6
std::cout << jref << '\n';          // display 48.5;
/* 
When to Use Reference Arguments
There are two main reasons for using reference arguments:
   To allow you to alter a data object in the calling function
   To speed up a program by passing a reference instead of an entire data object
The second reason is most important for larger data objects,such as structures and class
objects.These two reasons are the same reasons you might have for using a pointer argu-
ment.
    This makes sense because reference arguments are really just a different interface for pointer-based code.So when should you use a reference? Use a pointer? Pass by value?
The following are some guidelines.

A function uses passed data without modifying it:
    If the data object is small,such as a built-in data type or a small structure,pass it
by value.
    If the data object is an array,use a pointer because that’s your only choice.Make the
pointer a pointer to const.
    If the data object is a good-sized structure,use a const pointer or a const reference
to increase program efficiency.You save the time and space needed to copy a struc-
ture or a class design.Make the pointer or reference const.
    If the data object is a class object,use a const reference.The semantics of class
design often require using a reference,which is the main reason C++ added this
feature.Thus,the standard way to pass class object arguments is by reference.

A function modifies data in the calling function:
    If the data object is a built-in data type,use a pointer.If you spot code like
fixit(&x),where x is an int,it’s pretty clear that this function intends to modify x.
    If the data object is an array,use your only choice:a pointer.
    If the data object is a structure,use a reference or a pointer.
    If the data object is a class object,use a reference.
Of course,these are just guidelines,and there might be reasons for making different
choices.For example,cin uses references for basic types so that you can use cin >> n
instead of cin >> &n. */

Someclass::Someclass(const Someclass &);  // defaulted copy constructor
Someclass::Someclass(Someclass &&);       // defaulted move constructor

Someclass & Someclass::operator(const Someclass &);  // defaulted copy assignment
Someclass & Someclass::operator(Someclass &&);       // defaulted move assignment