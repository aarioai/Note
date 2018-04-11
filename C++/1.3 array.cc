/**
 * T *ampersand = new T;   // not arr, a T ptr to a heap sizeof T
        delete ampersand;
        ampersand = new T[N]; // ptr to another heap
        delete [] ampersand;
 * T *parenthesis = new T[N];  // an arr, a T ptr to a heap sizeof T[N]
        delete [] parenthesis;
 * T *p[n]
        int a = 100, b= 200;
        int *p[2] = {&a, &b};
        int **pp = p;
        char *pace[] = {"Lef", "Well"};
 * T (*p)[n]
        int a[1][2] = {{100, 200}};
        int (*p)[2] = a;
 * T (*p)(T-args)
        T origin(T-args){}
        T (*pfunc)(T-args);
        pfunc = origin;   // pfunc = &origin;
        T c = (*pfunc)(100);   // c = 100
 * T **p
 * T (*[const] muteness[N])()       an array with N elems. pointing to T ()
 */



/**
 * int accent[3][2] = {{111,222}, {333,444}, {555,666}};
        111        222        333        444        555        666
        x00        x04        x08        x12        x16        x20
    >>>>
        &accent[0][0]  accent[0]  accent  &accent  *accent      0x7f..00
          &accent[0][1]  accent[0]+1                              0x7f..04
        &accent[1][0]  accent[0]+2  accent[1]  accent+1            0x7f..08
          &accent[1][1]                                              0x7f..0c
        &accent[2][0]  accent+2                                    0x7f..10
          &accent[2][1]                                              0x7f..14
    >>>>
        *accent                                                    0x7f..00
        *accent[0]  *(*accent)    **accent                        111
                    *(*accent+1)                                  222
        *accent[1]    *(*accent+2)  **(accent+1)                    333
        *accent[2]                                                555    
    >>>>
        int (*accentuate)[2] = accent;
        

 */
int (*accented())[2] {
    // int (*accentuate)[2] = new int[2][3][4];   int accentuate[][2];
    int (*accentuate)[2] = (int (*)[2]) malloc(3*2*sizeof(int));
    //int **accentuate = (int **) malloc(3*2*sizeof(int));
    int accent[3][2] = {111,222,333,444,555,666};
    //int (*accentuate)[2] = accent;
    accentuate = accent;
    return accentuate;
}


/**
 *  {
        {{101..},{105..},{109..}},
        {{112..},{116..},{120..}}
    }
    >>>>
        ***accentuator                                    111
        ***(accentuator+1)                112                            
 */

int (*emphasize())[3][4]{
    // int (*accentuation)[3][4] = new int[2][3][4];
    //int (*accentuation)[3][4] = (int(*)[3][4]) malloc(2*3*4*sizeof(int));
    int ***accentuation = (int ***) malloc(2*3*4*sizeof(int));
    int accentuator[2][3][4] = {101, ... ,124};
    //int (*accentuation)[3][4] = accentuator;
    accentuation = accentuator;
    return accentuation;
}

int (*emphasis)[3][4] = emphasize();




/**
 * There is no array parameters, it's a pointer in deed.
 */
void sedimantary(int aspect[3]) {   // int *
    cout << sizeof(aspect);   // 8 --> int *, not 12
    
}
void hydropower(int (&diverse)[3]) {    // a 3 elements array argument
    cout << sizeof(a);  // 12 --> int (&)[3]
}

int extinct[3] = {100,200,300};  // sizeof(extinct) = 12
int impact[10] = {0,1,2,3,4,5,6,7,8,9};
cout << sizeof(impact);  // 40
sedimantary(extinct);   // it works, int *aspect = impact;
sedimantary(impact);      // it works, int *aspect = impact;
hydropower(extinct);    // it works, int (&)[3] to int [3]
hydropower(impact);     // Error: int(&)[3] to int[10]



Toad *toad = new Toad[3];  // ptr array




int a1[2];   // declaration, a1={1,2} or a1[0]=1; a1[1]=2;

int a2[2] = {1,2};  //initializing arrays
    
// same sa
int a2[] = {1,2};
//same as 
int a2[]{1,2};



int * c1 = new int[2]; // * c1 = {1, 2};  or c1[0] = 1; c2[1] = 2;
delete []c1;  // delete pointer
    
int * c2 = a2;   // c2[0] equals *c2, the first element of an array
int * c3 = &a2[0];  // the address of this array, equals &a2
int x = * (&a2);  // * (&a2[0])  == a2[0]

int * c4 = a2 + 1;  // the right value must be address, a2 = &a2 = &a2[0]
// it's &a2[0] + 1 =  &a2[1]
int y = * (a2 + 1);  // a2[1]

    
const int a8[2];   // declaration, a8={1,2};  CAN'T a8[0]=1;
const int * c8 = new int[2]; // *c8 = {1, 2}; CAN'T c8[0]=1;

/************************* valarray ****************************/
#include <valarray>
typedef std::valarray<int> ArrayInt;
int v0[3] = {10, 20, 30};
ArrayInt v1; // size 0 array
ArrayInt v2(2);  // size 2 array
ArrayInt v3(0, 2);  // {0, 0}, size 2, and initializing each to 0
ArrayInt v4(v0, 2);  // {10, 20}

std::valarray<int, 1> arr;

for(int i : a2) cout << i <<endl;  // will output 1, 2
    
    
/************************* array ****************************/    
#include <array>

std::array<int, 2> a;   // 2 ints
a = {2, 4};
    
    
/************************* char array **********************/
// a char array is end with \0
    
char fetal[] = {'f', 'e', '\0', 't', 'a', 'l'};
// strlen(fetal)  is 2  ==> "fe", ignore every chars after '\0'
char fetal = "fe\0tal";  // strlen(fetal) is 2
    
    