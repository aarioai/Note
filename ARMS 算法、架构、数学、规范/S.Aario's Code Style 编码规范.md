# Basic Code Style 基础规范
* Indents with `Tab` character   （使用 `Tab` 字符，而不是用空格）
* Abbreviations must be captiliazed. e.g. parseURL() URI()  （缩略词命名全大写，如 parseURL() URI()）
* Declaration Order (申明顺序)
	1. Typedefs and Enums   （类型、枚举）
	2. Constants (static const data members)  （常量、静态变量、变量）
	3. Constructors  （构造函数）
	4. Destructor    （析构函数）
	5. Methods, including static methods  （静态方法、动态方法）
 	> private --> protected --> public
 	> const --> static --> variable
 
```
type header struct {
	// BM is an abbreviation   （注意 BM 是缩略词）
	sigBM           [2]byte
	fileSize        uint32
}
const (
	TabsAndIndents = "Use Tab Character"
	name = "Aario"
	LuexuURL = "luexu.com"
)

```
# C++ Code Style
## Mutually Exclusive
* Declaration Order
 
## Save source file as .cc and header file as .h
The Google style guide suggests saving source file as (.cc). Header files should be self-contained and end in (.h). Files that are meant for textual inclusion, but are not headers, should end in (.inc).

All header files should be self-contained.

If a template or inline function is declared in a .h file, define it in that same file. The definitions of these constructs must be included into every .cc file that uses them, or the program may fail to link in some build configurations. Do not move these definitions to separate -inl.h files.

In general, every source file should have an associated header file. There are some common exceptions, such as unit-tests and small .cc files containing just a main() function.

* Unix: C, cc, cxx, c
* GNU C++: C, cc, cxx, cpp, c++
* Microsoft Visual C++: cpp, cxx, cc
* Digital Mars: cpp, cxx
* Borland C++: cpp
* Watcom: cpp
* Metrowerks CodeWarrior: cpp, cp, cc, cxx, c++

### Exclusion
As an exception, a function template that is explicitly instantiated for all relevant sets of template arguments, or that is a private member of a class, may be defined in the only .cc file that instantiates the template.

## Related header, C lib, C++ lib, other lib, your header file
Use standard order for readability and to avoid hidden dependencies: Related header, C library, C++ library, other libraries' .h, your project's .h.
```
#include "foo/server/fooserver.h"       // related header files

#include <sys/types.h>                  // C lib
#include <unistd.h>
#include <hash_map>                     // C++ lib
#include <vector>

#include "base/basictypes.h"            // self-defined headers
#include "base/commandlineflags.h"
#include "foo/server/bar.h"
```

## Define functions inline only when they are less than 10 lines
## When defined a function, parameter order is: inputs, then outputs
## Namespace
Unnamed namespaces are allowed and even encouraged in .cc files, to avoid link time naming conflicts:

Do not use unnamed namespaces in .h files.

## Nonmember, Static Member, and Global Functions
Prefer nonmember functions within a namespace or static member functions to global functions; use completely global functions rerely.

## Struct only for passive objects; everything else is a class. +|
structs should be used for passive objects that carry data, and may have associated constants, but lack any functionality other than access/setting the data members. Methods should not provide behavior but should only be used to set up the data members, e.g., constructor, destructor, Initialize(), Reset(), Validate().

Make data members private, and provide access to them through accessor functions as needed (for technical reasons, we allow data members of a test fixture class to be protected when using Google Test). Typically a variable would be called foo_ and the accessor function foo(). You may also want a mutator function set_foo(). Exception: static const data members (typically called kFoo) need not be private.

The definitions of accessors are usually inlined in the header file.

## Avoid doing complex initialization in construction
In particular, initialization that can fail or that requires virtual method calls. Constructors should never call virtual functions or attempt to raise non-fatal failures. If you object requires non-trivial['tr?v??l] initialization, consider using a factory function or init() method.

## Use 'explicit' for constructors callable with one argument

## All parameters passed by reference must be labeled const.
In C, if a function needs to modify a variable, the parameter must use a pointer, eg int foo(int *pval). In C++, the function can alternatively declare a reference parameter: int foo(int &val).

Input parameters may be const pointers, but we never allow non-const reference parameters except when required by convention, e.g., swap().

However, there are some instances where using const T* is preferable to const T& for input parameters. For example:
You want to pass in a null pointer.

The function saves a pointer or reference to the input.

Remember that most of the time input parameters are going to be specified as const T&. Using const T* instead communicates to the reader that the input is somehow treated differently. So if you choose const T* rather than const T&, do so for a concrete reason; otherwise it will likely confuse readers by making them look for an explanation that doesn't exist.

## Make data member private, provide access to them
## Avoid using dynamic_cast() abusively
RTTI(Run Time Type Information) allows a programmer to query the C++ class of an object at run time. This is done by use of typeid or dynamic_cast.

RTTI has legitimate[l?'d??t?m?t] uses but is prone[pr??n] to abuse, so you must be careful when using it. In particular, think twice before using RTTI in new code. If you find yourself needing to write code that behaves differently based on the class of an object, consider one of the following alternatives to querying the type:

    Virtual methods are the preferred way of executing different code paths depending on a specific subclass type. This puts the work within the object itself.
    
    If the work belongs outside the object and instead in some processing code, consider a double-dispatch solution, such as the Visitor design pattern. This allows a facility outside the object itself to determine the type of class using the built-in type system.
    
When the logic of a program guarantees[?g?r?n't??] that a given instance of a base class is in fact an instance of a particular derived class, then a dynamic_cast() may be used freely on the object. Usually one can use a static_cast as an alternative in such situations.

Decision trees based on type are a strong indication that your code is on the wrong track.
```
if (typeid(*data) == typeid(D1)) {
  ...
} else if (typeid(*data) == typeid(D2)) {
  ...
} else if (typeid(*data) == typeid(D3)) {
...


bool Base::Equal(Base* other) = 0;
bool Derived::Equal(Base* other) {
  Derived* that = dynamic_cast<Derived*>(other);
  if (that == NULL)
    return false;
  ...
}
```
## Use C++ casts instead of C casts
Use static_cast as the equivalent of a C-style cast that does value conversion, or when you need to explicitly up-cast a pointer from a class to its superclass.
Use const_cast to remove the const qualifier (see const).
Use reinterpret_cast to do unsafe conversions of pointer types to and from integer and other pointer types. Use this only if you know what you are doing and you understand the aliasing issues.

## Use streams only for logging
Do not use streams, except where required by a logging interface. Use printf-like routines instead.
There are various pros and cons to using streams, but in this case, as in many other cases, consistency trumps the debate. Do not use streams in your code.
|+ Use int16_t, uint32_t, int64_t in <stdint.h> +|
standard: int, size_t, ptrdiff_t
stdint.h: int8_t, uint8_t, int16_t = short, int32_t, uint32_t, int64_t, uint64_t
|[
for(uint32_t i = -1; i >= 0; --i){
    // Error: it'll never terminate! Because i is unsigned
}
]|

## Prefer inline functions, enums, and const variables to macros
The following usage pattern will avoid many problems with macros; if you use macros, follow it whenever possible:

Don't define macros in a .h file.

#define macros right before you use them, and #undef them right after.
Do not just #undef an existing macro before replacing it with your own; instead, pick a name that's likely to be unique.
Try not to use macros that expand to unbalanced C++ constructs, or at least document that behavior well.
Prefer not using ## to generate function/class/variable names.

## Use 0 for int, 0.0 for real, nullptr (or NULL) for ptr, and '\0' for chars
## Prefer sizeof(varname) to sizeof(type)
## auto is permitted, for local variables only

# PHP Code Style
## Uses absolute path to include/require a file.
    e.g.  include __DIR__ . '/../../vince.php';
## Omits the last end of PHP delimiter ('?>') in pure PHP files;
## Uses PHP_EOL to replace '\r\n'
* Excepts "\r\n", using single quotation to quote string.
```php
	echo 'I am Aario. ',PHP_EOL , 
		'My Email is Aario@luexu.com';
```
* In order not to match the system functions, don't use underline to name variables and parameters

    e.g. PHP system functions $_GET $_POST __unset __construct ...

* Uses exit() , Exit() and die() are equivalent.

    e.g. $fp=fopen('./readme.md','r') or exit('Error');

* Release memory-costed array or string (read from a large file) a.s.a.p. Evaluates a value to null instead of unset() it, because unset() only destroys the value of a variable, but not release memory 

    e.g. $a = [.........];   $a = null;  ( DON't use unset($a)  )

* Uses $_SERVER['REQUEST_TIME'] instead of time() to get the view time. Not for Swoole.
        

* Adds a back-slash when new a class (ext or namespace)
    e.g. $mysqli = new \mysqli(....);   $tf = new \Tf\Aaron\Test();   