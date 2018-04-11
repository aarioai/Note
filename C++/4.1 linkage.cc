
char a[5] = "hello";  // variable, you can change it like a[0] = 'x';  then a[] = "xello"
const char a[5] = "hello"; // unchangeable
char * p = new char[5]; // you can change it, p ="hello";
// you cant change p[0] = 'x' as well as you had initialled p="hello";
char * a = "hello";  // you can change the full string, like a="yes";
// but you cant use a[0] = 'x';
const char * a = "hello";  // unchangeable

const char * const months[2] ={"January", "February"};
/* In this example,the first const protects the strings from change,and the second const
makes sure that each pointer in the array remains pointing to the same string to which it
pointed initially. */


/**
  * External linkage, it can be used in all files in this program.
  */
int global = 1;  // static duration, external linkage

/**
  * Internal linkage, it can be used only in the file containing this code
  */
static int one_file = 2;  // static duration, internal linkage
void func(int n){
    /**
     * The variable static_in_func can be used only inside the func. 
     * But it remains in memory even when the func() is not being executed.
     */
    static int static_in_func = 3;   //static duration, no linkage
}

/*
All static duration variables share the following initialization feature:An uninitialized
static variable has all its bits set to 0.Such a variable is said to be zero-initialized.

On the one hand, an external variable has to be declared in each file that uses the variable.
On the other hand, C++ has the ¡°one definition rule¡± (also known as odr), which states
that there can be only one definition of a variable.To satisfy these requirements, C++ has
two kinds of variable declarations. One is the defining declaration or, simply, a definition.It
causes storage for the variable to be allocated.The second is the referencing declaration or,
simply, a declaration. It does not cause storage to be allocated because it refers to an existing
variable.
A referencing declaration uses the keyword extern and does not provide initialization.
Otherwise, a declaration is a definition and causes storage to be allocated:

If you use an external variable in several files, only one file can contain a definition for
that variable (per the one definition rule). But every other file using the variable needs to
declare that variable using the keyword extern:
*/
    
// file01.cpp
int cats = 20;  // definition because of initialization
int dogs = 22;         // also a definition
int fleas;             // also a definition

// file02.cpp
// use cats and dogs from file01.cpp
extern int cats;       // not definitions because they use
extern int dogs;       // extern and have no initialization
...
// file98.cpp
// use cats, dogs, and fleas from file01.cpp
extern int cats;
extern int dogs;
extern int fleas;

/* 
In this case,all the files use the cats and dogs variables defined in file01.cpp.How-
ever,file02.cpp doesn¡¯t re-declare the fleas variable,so it can¡¯t access it.
 */

