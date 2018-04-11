/* Some languages use the idea of l-values and r-values. L-values have storage addresses that are programmatically accessible to the running program (e.g., via some address-of operator like "&" in C/C++), meaning that they are variables or dereferenced references to a certain memory location. R-values can be l-values (see below) or non-l-values—a term only used to distinguish from l-values. Consider the C expression (4 + 9). When executed, the computer generates an integer value of 13, but because the program has not explicitly designated where in the computer this 13 is stored, the expression is an r-value. On the other hand, if a C program declares a variable x and assigns the value of 13 to x, then the expression (x) has a value of 13 and is an l-value.

In C, the term l-value originally meant something that could be assigned to (hence the name, indicating it is on the left side of the assignment operator), but since 'const' was added to the language, the term is now 'modifiable l-value'. In C++11 a special semantic-glyph "&&" exists, to denote the use/access of the expression's address for the compiler only; i.e., the address cannot be retrieved using the address-of, "&", operator during the run-time of the program (see the use of move semantics).

This type of reference can be applied to all r-values including non-l-values as well as l-values. Some processors provide one or more instructions which take an immediate value, sometimes referred to as "immediate" for short. An immediate value is stored as part of the instruction which employs it, usually to load into, add to, or subtract from, a register. The other parts of the instruction are the opcode, and destination. The latter may be implicit. (A non-immediate value may reside in a register, or be stored elsewhere in memory, requiring the instruction to contain a direct or indirect address [e.g., index register address] to the value.)

The l-value expression designates (refers to) an object. A non-modifiable l-value is addressable, but not assignable. A modifiable l-value allows the designated object to be changed as well as examined. An r-value is any expression, a non-l-value is any expression that is not an l-value. One example is an "immediate value" (look below) and consequently not addressable.

The notion of l-values and r-values was introduced by CPL. The notions in an expression of r-value, l-value, and r-value/l-value are analogous to the parameter modes of input parameter (has a value), output parameter (can be assigned), and input/output parameter (has a value and can be assigned), though the technical details differ between contexts and languages. */

/* 
  左值具名，对应指定内存域，可访问；右值不具名，不对应内存域，不可访问。临时对像是右值。左值可处于等号左边，右值只能放在等号右边。区分表达式的左右值属性有一个简便方法：若可对表达式用 & 符取址，则为左值，否则为右值。
     注意区分 ++x 与 x++。前者是左值表达式，后者是右值表达式。前者修改自身值，并返回自身；后者先创建一个临时对像，并用 x 的值赋之，后将修改 x 的值，最后返回临时对像。
 */
int moan = 10;
int mob = 50;
int & refactory = moan;
int && mover = 10;  // rvalue


void staff(double & rs);         // matches modifiable
void staff(const double & rcs);  // matches rvalue, co
void stove(double & r1);         // matches modifiable
void stove(const double & r2);   // matches const lval
void stove(double && r3);        // matches rvalue
/* This allows you to customize the behavior of a function based 
rvalue nature of the argument: */
double x = 55.5;
const double y = 32.0;
stove(x);             // calls stove(double &)
stove(y);             // calls stove(const double &)
stove(x+y);           // calls stove(double &&)
/* If, say, you omit the stove(double &&) function, then stove
stove(const double &) function instead.
 */

