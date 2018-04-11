/* 
As programmers become more familiar with namespaces,common programming idioms
will emerge.Here are some current guidelines:
    Use variables in a named namespace instead of using external global variables.
    Use variables in an unnamed namespace instead of using static global variables.
    If you develop a library of functions or classes,place them in a namespace.Indeed,
C++ currently already calls for placing standard library functions in a namespace calledstd.This extends to functions brought in from C.For example,the math.c
header file,which is C-compatible,doesn’t use namespaces,but the C++ cmath
header file should place the various math library functions in the stdnamespace.
    Use the usingdirective only as a temporary means of converting old code to
namespace usage.
    Don’t use using directives in header files;for one thing,doing so conceals which
names are being made available.Also the ordering of header files may affect
behavior.If you use a using directive,place it after all the preprocessor #include
directives.
    Preferentially import names by using the scope-resolution operator or a using
declaration.
    Preferentially use local scope instead of global scope for using declarations.

 */


namespace Inspector {
    double bucket(double n){...}
    double fetch;
    namespace miner{  // nested namespace
        
    }
    struct inspect{
    }
}

namespace Proprietor {
     double wage;
}
namespace Coalman {
    using namespace Inspector;   // Coalman has the same elements as Inspector has
    using Prorietor::wage;
 // you can use Coalman::wage, or Coalman::fetch;
}


namespace Miner = Coalman;   // an alias
namespace Prospect = Inspector::inspect;  // an alias to nested namespace


Inspector::fetch = 1.1;


using Inspector::fetch;  // a using declaration
cin >> fetch;  // read a value into Inspector::fetch
cin >> ::fetch;  // read into global fetch

//Placing ausingdeclaration at the external level adds the name to the global namespace.

 /* In contrast, the using directive makes all the names available.A using directive involves preceding a namespace name with the keywords using namespace, and it makes all the names in the namespace avail-able without the use of the scope-resolution operator: */

using namespace Inspector; // a using directive



/* 
If a particular name is already declared in a function,you can’t import the same name with a using declaration.
When you use a using directive,however,name resolution takes place as if you declared the names in the smallest declarative region containing both the using declaration and the namespace itself.
 */
 
 char fetch;   // global fetch
    int main() {
        // double fetch;  not here, otherwise, clash with namespace Inspector's fetch
        using namespace Inspector;
        double coal = bucket(2); // use Inspector::bucket();
        double fetch; // not an error; hides Inspector::fetch
        cin >> fetch;  // read into the local fetch
        cin >> ::fetch;  //read into global fetch
        cin >> Inspector::fetch;
    }
 
 /* Suppose a namespace and a declarative region both define the same name. If you attempt
to use a using declaration to bring the namespace name into the declarative region,the
two names conflict,and you get an error. If you use a using directive to bring the name-
space name into the declarative region,the local version of the name hides the namespace
version. */




static int counts;  // static storage, internal linkage
// use namespace approach instead:
namespace {
    int counts;  // static storage, internal linkage
}






 