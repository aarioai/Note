/**
 * "const_cast" will remove cv-qualified(const/volatile) keywords, make "const T*" to "T *". it works, but not suggest.
 * it'll makes const T * changeable, but const T unchangeable
 */
const int exposure = 100;   // 0x7f..a0
const int * meteorite = &exposure;

int *exponent = (int *)(&exposure) = (int *)(0x7f..a0);
int *deserve = const_cast<int *>(&exposure) = const_cast<int*>(0x7f..a0);


// char *desexualize = (char *)(&exposure); // *desexualize = 'd'
char *desexualize = reinterpret_cast<char *>(&exposure);

char *sterilize = const_cast<char *>(&exposure);//Err, "const int *" to "char *"

int *facial = const_cast<int *>(meteorite);  // int *facial = (int *)meteorite;

*deserve = 300;
printf("%d %p", exposure, &exposure);               // 100 0x7f..a0 -- const int
printf("%d %p", *meteorite, meteorite);             // 300 0x7f..a0
printf("%d %p", *deserve, &deserve);                // 300 0x7f..a0
printf("%d %p", *facial, facial);                   // 300 0x7f..a0


int expose = 500; // const int exposed = expose;  it works, "int" to "const int"
const int *meteor = &expose;    // it works, "int *" to "const int *"
int *desert = const_cast<int *>(&expose); // int *desert = (int *)(&expose);
*desert = 600; 
printf("%d %p", expose, &expose);                   // 600 0x7f..a0 -- int
printf("%d %p", *meteor, meteor);                   // 600 0x7f..a0
printf("%d %p", *desert, desert);                   // 600 0x7f..a0



/**
  * mutable
  * Now let¡¯s return to mutable.
  * a particular member of a structure (or class) can be altered
  * even if a particular structure (or class) variable is a const. 
  */
  
struct data {
    char name[30];  
    mutable int accesses;
};

const data veep = {"Adam", 0};
strcpy(veep.name, "Well");   // not allowed
veep.accesses++;                  // allowed

/* 
The const qualifier to veep prevents a program from changing veep¡¯s members, but
the mutable specifier to the accesses member shields accesses from that restriction.
 */
 
/*  In C++ (but not C), the const modifier alters the default storage classes slightly.Whereas
a global variable has external linkage by default, a const global variable has internal link-
age by default.That is, C++ treats a global constdefinition, such as in the following code
fragment, as if the static specifier had been used: */
const int fingers = 10;    // same as static const int fingers = 10;
extern const int fingers = 10;  // external linkage