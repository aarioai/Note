/**
 * Null Ptr Constant: An integer constant expression with the value 0, 
 *  or such an expression cast to type void *
 *  e.g. 0, 0L, 3-3, (void*)0 are all null ptr constants ((char*)0 is not)
 * Null Ptr: the resulting ptr that coverted from a null ptr constant
 *  be guaranteed to compare unequal to a ptr to any obj or func, which means 
 *  the addr. of any obj or func are all not a null ptr
 *  e.g T *p; ==> p=NULL; p=0; p=0L; p='\0'; p=0*12; p=(void*)0;
 *  * if the space cannot be allocated (by malloc), a null ptr is returned
 * NULL: a null ptr constant. Self-defined NULL is illegal. it's a macro that 
 *  defined as 0:   #define NULL 0
 */


/**
 * T *     a T pointer
 * T **    a pointer that points to "T *"
 * T *&    a reference that points to "T *"
 */
Expound *expound;   // an "Expound *" pointer
Expound *expositor = expound; // an "Expound *" pointer that points to an addr.
Expound *interpret[100];  // an array with 100 "Expound *" pointers
Expound **exposition = interpret; // a pointer that points to another pointer

/**
 *  "T *"           to "const T *"      bingo
    "T **"          to "const T **"     Err
    "derivedCls *"  to "baseCls *"      bingo
    "derivedCls **" to "baseCls **"     Err
 */
int discord = 100;
const int *discourse = &discord;  // it works, "int *" to "const int *"
char *discredit[3];
char ** discreditable = discredit; // it works
const char **discovert = discredit; // Err, "char **" to "const char **" 



void gemstone(const char **gem, char cameo) {
    while(**gem && **gem != cameo)
        ++ *gem;    // ++asterism
    printf("gemstone *gem: %s", *gem);
}

void geminate(const char *&gem, char cameo) {   // Suggest 
    while(*gem && *gem != cameo)
        ++gem;
    printf("geminate gem: %s", gem);
}

const char * asterism = "bait";
/**
 *      astatic = &asterism
        *astatic = asterism
        **astatic = *asterism
 */
const char ** astatic = &asterism;

gemstone(&asterism, 'a');
geminate(asterism, 'a');





/**
 *  T *predawn = new T;
    const T *predator;      // a "predation" pointers to "const T"
        T const *predator;  // Same as above
    T *const predation; // a "const predation" pointers to T
    const T  *const predatory;      // a "const predatory" ponters to "const T"
        T const * const predatory;  // Same as above
    ****************************************************************************
    const T merchant;
    const T &comet = *predawn;   // a "comet" references to "const T"
        comet = merchant;  // Err: read-only 'comet'
    T merchantContainer;    
    T &erosion = *predawn;
        a reference is a right-value, &comet = 300;  is Err!
        erosion = merchantContainer; // it works
 */
 

const int exposure = 100;
const int nausea = 200;
const int *meteorite = & expsure;
// *meteorite = 200;   Err: read-only *meteorite, it's "const int"
meteorite = &nausea; // points to another "const int"

// int *marin = &exposure;  Err: const int* to int*
// int *transplant = meteorite;   Err: const int* to int*

int desiccate = * const_cast<int *>(&exposure);  // int desiccate = 100;
int designate = 200;
int *const desiccant = &desiccate;
*desiccant = 500;  // 
/*
 * desiccant = const_cast<int *const>(&nausea);
 * Err: assignment of read-only variable 'desiccant'
 */
desiccant = &designate;  // Err: 



const int &desirous = designate;  // it works, "int" to "const int"
    desirous = desiccate;  // Err: read-only desirous
    &desirous = desiccate; // Fatal Err:
int &desist = designate;
    desist = desiccate; // it works, 






















/* Pointers and Objects Summary
You should note several points about using pointer s to objects (refer to Figure 12.5 for a
summary): */
//You declare a pointer to an object by using the usual notation:
String * glamour;
//You can initialize a pointer to point to an existing object:
String * first = &sayings[0];
//You can initialize a pointer by using new.The following creates a new object:
String * favorite = new String(sayings[choice]);
// Also see Figure 12.6 for a more detailed look at an example of initializing a pointer with new.
//Using new with a class invokes the appropriate class constructor to initialize the newly created object:
// invokes default constructor
String * gleep = new String;

// invokes the String(const String &) constructor
String * favorite = new String(sayings[choice]);
// You use the ->operator to access a class method via a pointer:
if (sayings[i].length() < shortest->length())
// You apply the dereferencing operator (*) to a pointer to an object to obtain an object:
if (sayings[i] < *first)    // compare object values
first = &sayings[i];   // assign object address





/*************************************************************************/
const char * sediment  = "Aario";  // or char sediment[] = "Aario"
const char * deposit = sediment;
const char * precipitate = "-AARIO-AI-";
deposit = precipitate;
cout << deposit;   //  -AARIO-AI-
cout << sediment;  // Aario
/*************************************************************************/



/*************************************************************************/
short a = -1;  // the binary is :  1[ thirty zeros ]1
unsigned short b = * (short *)&a;  // 1[ thirty zeros ]1  2^15+1

/*************************************************************************/




/*************************************************************************/
int a = 100; // &a = 00CEFEC4
/**
  * cast from hex to int
  */
int b = (int) &a;  // 00CEFEC4 = 13565636  cast to int
/**
 * b is an int, but c is a pointer to int x's address
 * cast from int to (int *)
 */
int *c = (int *) b;  
int *d = (int *) 13565636;   // same as *c
/*************************************************************************/

/**
  * rats is in stack [0xFFFF] the value is 100
  */

int rats = 100;

/**
 * rodents is an reference to int rats;
 * which means rodents is an alias for rats
 * so &rodents = &rats = [0xFFFF]
 * rodents = 100;
 */
int & rodents = rats;


/**
 * pussies is a pointer to int-rats's address
 * it's a pointer, not alias. so the address is  stack [0xFFDD]
 * [0xFFDD] -> [0xFFFF]
 * so *pussies = rats, pussies = &rats
 */
int * pussies = &rats;




/**
 * &kitten = [0xFFCC]
 * [0xFFCC] -> [0xFFDD] -> [0xFFFF]
 */
int * kitten = pussies;

/**
 * &pony = [0xFFBB]
 * [0xFFBB] -> [0xFFFF] => {0x0000}
 */
int * pony = &rodents;



/**
 * reset [0xFFFF] 's value 200
 * so *pussies = 200 
 * so *kitten = 200
 * so rodents = 200
 */
rats = 200;

/**
 * puppy is a pointer to a int, it points to pony 
 * so *puppy = 200
 * [0xFFAA] -> [0xFFBB] -> [0xFFFF]
 */
int * puppy;
puppy = pony;  
// same as 
int * puppy2 = (int *) pony;  // cast pony to address (actually it is)

int * pointy = (int *) 10000;  // cast 10000 to address


/**
 * set address pony ([0xFFFF]) 's value to 300
 * [0xFFBB] -> [0xFFFF]
 */
*pony = 300;


int * chick;   // CAN'T int * chick = 10; or int * chick; * chick=10;
chick = (int*)malloc(sizeof(int));  // sizeof(int) = 4
// malloc(4) is void *, it's a address like
*chick = 10;

int * pi = new (std::nothrow) int;



// int * pussies = rats;  it's fatal error

/**
 * squirrels is a pointer
 * squirrels equals "squirrels"
 * pointer *squirrels equal "s"
 * 
 */
char * squirrels = "squirrels";

    
const char * lamb = "sheep"; //lamb is a pointer to const char same as char const * lamb; because there isn't const * in C++;
lamb = "another";  // okay

const int n=2; // same as int const n=2; you can exchange const's place with other types
    
  

char * const piglet = "piggy";  // piglet is a const pointer to char
// CAN'T piglet = "another";  

char ** pp;  // pointer to pointer to char  
    
    
/* In this context, & is not the address operator. Instead, it serves as part of the type identi-fier. Just as char * in a declaration means pointer-to-char, int & means reference-to-int.The reference declaration allows you to use rats and rodents interchangeably; both refer to the same value and the same memory location. Listing 8.2 illustrates the truth of this claim.

Then you could use the expressions rodents and*prats interchangeably with rats and use the expressions &rodents and prats interchangeably with &rats.From this standpoint,a reference looks a lot like a pointer in disguised notation in which the * dereferencing operator is understood implicitly.And,in fact,that’s more or less what a reference is.But there are differences besides those of notation.
For one,it is necessary to initialize the reference when you declare it; you can’t declare the reference and then assign it a value later the way you can with a pointer: */
int rat;
int & rodent;
rodent = rat;   // No, you can't do this. You should initialize a reference variable when you declare it.

A reference is rather like a const pointer; you have to initialize it when you create it, and when a reference pledges its allegiance to a particular variable, it sticks to its pledge.



int rats = 101;  // address 0x0066ff88
int & rodents = rats;  // reference, rodents equal rats, and &rodents equals &rats (0x0065fd44)
int bunnies = 50;  // address 0x00556677
rodents = bunnies;  // & rodents is a reference to rats, they share the same address(0x0065fd44)
cout << rats << endl;  // print 50



int rats = 101;   // address 0x0066ff88
int * pussies = &rats;    // *pussies is a pointer to address 0x0066ff88, *pussies equals rats
int & rodents = *pussies;  // reference to *pussies (address is 0x0066ff88)
int bunnies = 50;  // adress 0x00556677
pussies = &bunnies;  // pointer to new address 0x00556677

cout << *pussies << endl;  // 50
cout << rats << endl;   // 101
cout << rodents << endl;  // a reference to 0x0066ff88, 101



/*********************  && **************************/

int && dinosaur = 100; // dinosaur = 100, &dinosaur is address
int && fossil = 100 + 100;









