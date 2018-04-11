/**
 * placement new
 */

class Sewage {
    public:
    ~Sewage(){}
/******************** 1 ***********************/
    T *operator new(size_t, T *ptr) throw() {
        return ptr;
    }
/******************** 2 ***********************/
    Sewage *operator new(size_t,T * ptr) throw() {
        return reinterpret_cast<Sewage *>(ptr);
    }
/********** Keep one of above only ************/
};

Sewage *sewage_heap = new Sewage;  // operator new in heap
delete sewage_heap;  // run Sewage::~Sewage automatically
int sly = 100;
Sewage *sewage_stack = reinterpret_cast<Sewage *>(&sly);  // in stack
sewage_stack->Sweage();  // call destructor manually
void *stealth = reinterpret_cast<void *>(&sly);
Sewage *sewage_new = new (stealth) Sewage;  // placement new, in stack
sewage_new->Sweage();
Sewage *sewage_arr = new (stealth) Sewage[3];
for(int i=0;i<3;++i)
    *(++sewage_arr)->~Sewage();  // call each destructor manually
    //sewage_arr[i]->~Sewage();  






int digit = 8;
char * digital = (char *)&digit;
int figure = *(int *)digital;       // figure = 8


struct Fig{ int dab;};

Fig f = {100};
char * glut = (char *) &f;
Fig f2 = *(Fig *)glut;      // f2.dab = 100


struct Fatality { int fatalism, fatalist, fatally;}
Fatality fatal[] = {{1,2,3},{5,8,0}};
char * fate = (char *) &fatal;
Fatality * fated = (Date *) fate;  // * fated = {{1,2,3},{5,8,0}}

 
/******************************************************************************/
ofstream ofs("fatalness.txt", ios::binary);
ofs << fate;
ifstream ifs("fatalness.txt", ios::binary);
short len = sizeof(Fatality) / sizeof(int);

/**
 * char * fate2 = new char [sizeof(Fatality)];
 * ifs.read(fate2, sizeof(Fatality));
 * delete [] fate2;
 */
Fatality ft;
for(int i=0; i<len; i++){
    ifs.read((char *)&ft[i], sizeof(ft));
}



/******************************************************************************/








void
bool [false, true] 1-byte
short int / signed short int [-2^(2*8-1), 2^(2*8-1)] 2-bytes
long int / signed int [-2^(2*32-1), 2^(2*32-1)] 4-bytes
long long [0, 2^64] 8-bytes
char / signed char [-128, 127] 1-byte
unsigned char [0, 255] 1-byte
wchar_t [0, 2^16]
float [] 4-bytes 
double [] 8-bytes
long double 




int dint = 20;
// same as
int dint = {20};
// same as
int dint{20};

char meteor{65};
char meteor = {65};
char meteor = 'A';

char fester[] = {'f', 'e', 's', 't', 'e', 'r'};
//same as
char fester[] = "fes\0ter";
char fester[]{'f', 'e', 's', 't', 'e', 'r'};

char && robe = 'A';  // or char && robe = 65;
char && robe{'A'};
char && robe = {'A'};



const int pointed = 100;



void add(const int *p) {
    int * pc;
// The const_cast operator can cast away the const from const int * p, thus allowing the compiler to accept the add statement:
    pc = const_cast<int *>(p);
    *pc ++;
}

//However, because pointed is declared as const, the compiler may protect it from any change, as is shown by the following sample output:
add(&pointed); //  pointed = 100
add(&dint);  // now dint = 21



int * cast = (int *) & pointed;  // *cast is 100

/********************** decltype ***********************/

int a = 1;
decltype(a) x;  // x is type int
decltype (a) x = a;   // x is type int, it equals 1

decltype(&a) x = &a;  // x is type &a, a pointer double *,  *x = a
decltype ((a)) x = a;   // x is type int &, it reference to a
const int & b = 1;
decltype(b) x = a;  // x is type const int &, it reference to a

decltype (a+1) y;   // y is type int


double f(int a);     // is equivalent to
auto f(int a) -> double;