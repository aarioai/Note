typedef struct {
#ifdef __USE_XOPEN
    __fd_maskfds_bits[__FD_SETSIZE/__NFDBITS];
#define __FDS_BITS(set)((set)->fds_bits)
#else
    __fd_mask__fds_bits[__FD_SETSIZE/__NFDBITS];
#define __FDS_BITS(set)((set)->__fds_bits)
#endif
} fd_set;

fd_set rset, allset;
FD_ZERO(&allset);
FD_SET(listenfd, &allset);
FD_SET(fileno(stdin), &allset);
rset = allset;  // structure assignment
FD_CLR(listenfd, &allset);
FD_ISSET(listenfd, &allset);    // false
FD_ISSET(listenfd, &rset);  // true

/**
 * #define $var_nm $val
 */
 
/**
 * typedef $type_nm $alias_type_nm;
 */

const char * String() {return "Lef Well";}
typedef const char * Str ();
Str String{return "Lef Well";} 


void (*signal(int signo, void(*func)(int)))(int){}
typedef void Sig (int);
Sig (*signal(int signo, Sig * func)){}
typedef void (*Sig) (int);
Sig signal(int signo, Sig func){}




template <typename dash, typename pound>
struct Punctuate{
    pound operator()(typename hyphen) const {  // functor, not ptr
    return (pound)hyphen;
    }
};

Punctuate<int, bool>();  // overload operator()

/**
 * std::unary_function<T-arg-type, T-rtn-type>
        template <typename a, typename r>
        struct binary_function{  // a struct of std
            typedef a argument_type;
            typedef r result_type;
        };
    
 * std::binary_function<T-types1, T-type2, T-rtn-type>
        template <typename a, typename b, typename r>
        struct binary_function{  // a struct of std
            typedef a first_argument_type;
            typedef b second_argument_type;
            typedef r result_type;
        };
 */


 
struct Subtract: public std::unary_function<int, bool> {
    bool operator()(int subtraction) {   // functor, not ptr
        return subtraction > 0;
    }
}

Subtract(-100);  // false



/**
 *  sizeof(struct..)
        align to the largest number with sequence
        2 1 1   = 4 = 2 [11]
        1 1 2   = 4 = [11] 2
        1 2 1   = 6 = [1#] 2 [1#]
        1 2 1 1 = 6 = [1#] 2 [11]
        1 4 1 2 = 12 = [1###] 4 [1#2]
        1 4 3 2 = 16 = [1###] 4 [3#] [2##]
 */

/**
 * 32 = [4####] 8 [1#24] [4####]
 *  sizeof(int) = 4 bytes; 1 bytes = 8 bits
 * @note struct is quite different to allocate stack address
 */
struct Allergic {
    int wound;             // 0x7f..a0        4 bytes + 4
    const char* victim;    // 0x7f..a8        8 bytes --> largest number
    char respirate;        // 0x7f..b0        1 + 1
    short advantageous;    // 0x7f..b2
    int rodent;            // 0x7f..b4
    int sneezy;            // 0x7f..b8
};
struct Allergic {    // 
    int wound;             // 0x7f..a0        4 bytes + 4
    const char* victim;    // 0x7f..a8        8 bytes --> largest number
    char respirate;        // 0x7f..b0        1 + 1
    short advantageous;    // 0x7f..b2
    int rodent;            // 0x7f..b4
    int sneezy;            // 0x7f..b8
};                
Allergic allergic = {4, "victimize", 'V', 400, 444};
struct Allergic allergic = {4, "victimize", 'V', 400, 444};     // C-Style

typedef struct {                                // C-Style
    int vomit;
    const char* vomitus;
} Abnormality, *Seizure;

// abnormality = {4, "victimize"} 
Abnormality abnormality = allergic;    //Abnormality *abnormality = &allergic;
Seizure seizure = &allergic;  // Seizure *seizure = allergic;

typedef struct avian {                            // C-Style
    int subtle;
    const char* slight;
    char 
} Brutal;
struct avian bird = allergic;
Brutal *avian = &allergic;



/**
 * Assign the packing alignment in Struct and Union
 *    #pragma pack([ BYTES ?=8 ]);
        [ BYTES ]: 2^0, 2^1, 2^2, ?=2^3, 2^4 ...
 */

#pragma pack(2)
struct Allergic {     // 22 = [1#][8][1#][2][4][4]
    int wound;
    const char* victim;
    char respirate;
    short advantageous;
    int rodent;
    int sneezy;
}
 
#pragma pack(4)
struct Allergic {    // 24 = [1###][8][1#2][4][4]
} 
 
 
 

/**
 * sizeof(union..)
        the largest number
 */
union Suppress {        // 32 bytes
    double lethe;        // 8 bytes
    Allergic allergic;   //32 bytes
    float faeces;        // 4 bytes
};

Suppress supress = {120.33};

typedef union {                            // C-Style
    char c;            // 1 byte, and char is [-128, 127]
    int anarch;
    int bobby;
} Unionize;

Unionize u;
u.c = 0x0000007f;  //  127
cout << u.anarch;  //127
cout << u.boddy;   // 127

u.anarch = 383;  // 0x0000017f
int x = u.c;  // c is the last byte of the int(4 bytes) ==>7f
cout << x;  // 127

