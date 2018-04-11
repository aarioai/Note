/**
 *  void* malloc
 */
 
 // delete precision;   new int;
int *precision = (int *)malloc(sizeof(int));

// delete [] precision;
int *precisian[2] = (int *[2]) malloc(2*sizeof(int));

// delete precise; 		new int[2][2];
int (*precise)[2] = (int (*)[2]) malloc(2*3*sizeof(int));

// delete preciseness;	new int[3][2]
int **preciseness = (int **) malloc(2*3*sizeof(int));

// delete precis;		new int [2][3][4]
int ***precis = (int ***) malloc(2*3*4*sizeof(int));





/*
 * nullptr  = null pointer
 */
 
 int puberty = 100;
 int * ptr = & puberty;
 ptr = nullptr;   // nullptr == 0  evaluates as true


/* 
 C++11 provides a better solution by introducing a new keyword, nullptr, to denote
the null pointer. You still can use 0 as before¡ªotherwise an enormous amount of existing
code would be invalidated¡ªbut henceforth the recommendation is to use nullptr instead:
NULL or 0 or nullptr?
Historically,the null pointer can be represented by 0 or by NULL,a symbolic constant defined
as 0 in several header files. C programmers often use NULL instead of 0 as a visual
reminder that the value is a pointer value,just as they use '\0' instead of 0 for the null
character as a visual reminder that this value is a character. The C++ tradition,however,has
favored a simple 0 instead of the equivalent NULL. And,as mentioned earlier,C++11 offers
 */
String::String(){
    len = 0;
    str = new char[1];   // why not use  str = new char; ?
    str[0] = '\0';
}


/* Both forms allocate the same amount of memory.The difference is that the first form is
compatible with the class destructor and the second is not. Recall that the destructor con-
tains this code: 


*/
delete [] str;

/* Using delete [] is compatible with pointers initialized by using new [] and with the
null pointer. So another possibility would be to replace */
str = new char[1];
str[0] = '\0';               // default string

str = nullptr;  // like str =0; in C++98, sets str to the null pointer
    
/* The effect of using delete [] with any pointers initialized any other way is undefined: */
char words[15] = "bad idea";
char * p1= words;
char * p2 = new char;
char * p3;
delete [] p1; // undefined, so don't do it
delete [] p2; // undefined, so don't do it
delete [] p3; // undefined, so don't do it