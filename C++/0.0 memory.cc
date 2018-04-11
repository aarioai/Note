/**
 * allocate sz byte memory (may be used, need be initialized to 0 by memset(void *p, 0, sz))
 */
void *malloc(size_t sz)     
void *emalloc(size_t sz) {
  void *p = malloc(sz);
  if (p == NULL) {
    fprintf(stderr, "out of memory!\n");
    exit(1);
  }
  return p;
}       
void *free(void *p)
void *efree(void *p)


/**
 * realloc an old point and a new size.
 * e.g.
 *    const char *me = "Aario Ai";
 *    char *continuous = (char *)malloc(6 * sizeof(int));
 *    memcpy(continuous, me, 5);
 *    continuous[6] = '\0';
 *    print(continuous);          // Aario
 *    continuous = (char *)realloc(continuous, strlen(me));
                //  [A|a|r|i|o|\0| | | |\0]
 *    continuous[strlen(me)] = '\0';      // Aario
 */
void *realloc(void *p, size_t sz) 
void *erealloc(void *p, size_t sz)


/**
 * allocate n * sz bytes memory (already be initialized to 0)
 */
void *calloc(size_t n, size_t sz)
void *ecalloc(size_t n, size_t sz)







/**
 *
 *@see http://www.ibm.com/developerworks/library/j-nativememory-aix/
 *@see http://www.c-sharpcorner.com/uploadfile/c210df/how-memory-is-managed-by-stack-and-heap/


[Stack]
    It is the use of stack for function parameters and return values that makes it convenient to write recursive functions.
    由编译器自动分配释放 ，存放函数的参数名，局部变量的名等。其操作方式类似于数据结构中的栈。
[Heap]
    This area contains all objects which are created by new key word. 由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表。
[Data Regment]
    Data- Data area contains non zero or non null static and global variables. It consist of read only as well as read-write block.
    BSS(Block Started by Symbol)- It contains all global and static variables that are  initialized to zero or don't have any initialization at all.
    DS register is a 16-bit register containing address of 64KB segment with program data.Index register (SI, DI) are used to access all data on data segment
    全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域， 未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。程序结束后由系统释放。
[Code/Text segment]
  Contains all the executable code.CS register is a 16-bit register containing address of 64 KB segment with processor instructions. CS + IP(instruction pointer) gives the access to all instruction in the code segment.
    |-------------------------------|
    |          Physical RAM         |
    |-|-----------------------------|0xffffffffffffffff = 2^64
    | | avaliable for stack growth  |[Stack Reserved]
    |-|-----------------------------|0xffffffffffbf0000
    |S| system                      |
    |T| env-argv-argc               |
    |A| auto varibles for main()    |[Stack]
    |C| auto variables for func()   |
    |K|                             |
    |-|-----------------------------|
    |S| malloc.o (lib*.so)          |[Shared Library]   
    |L| printf.o (lib*.so)          |
    |-|-----------------------------|0xfffff7ff00000000
    | | avaliable for heap growth   |[Heap Reserved]
    |-|-----------------------------|0x80100000000
    |H| heap(malloc(),calloc(),new) |[Heap]
    |-|-----------------------------|
    |D| Unintial../Zero G/S Members |[Data] Uinitialized data - BSS Segment   
    |T| Global/Static variables     |       Initialized data - Data Segment
    |-|-----------------------------|
    |T| malloc.o/printf.o (lib*.a)  |
    |E| file.o                      |[Text]
    |X| main.o func()               |================== the return address
    |T| ctr0.o (startup routine()   |
    |-|*****************************|0x100000000 = 16^8 = 2^32
    | | OS Kernel                   |
    |-|-----------------------------|0x0

    
    |-------------------------------|
    | Process(a.out) AIX Virtual Mem|
    |-------------------------------|0xff..ff = 0xffffffffffff
    | Shared Library Data           |
    | Shared / Mapped               |
    | Shared Library Text           |
    |-------------------------------|
    | point to Page file            |
    | point to Physical RMA         |[Shared/Mapped Storage]
    | point to File System -> a.out |   {a.out b.out ...}
    |-------------------------------|
    | Stack + Data                  |
    |-------------------------------|
    | App Text Kernel               |
    |-------------------------------|0x0
      
        
*/

class Obsolete{
    int obsolescence;               // [Stack]
    Obj concept = new Ojb();        // [Heap]
    static int conceptual = 100;    // [Data-G/S Variables]
    T instance(){}                  // [Text]
};
T instantCoffee(){
    int instantaneous;  //  [Stack] [0x7f..3f]
    int instantNodles;  //  [Stack] [0x7f..3b]
}
struct Allergic{    // Note: struct is quite different to allocate stack address
    int wound;             // 0x7f..a0        4 bytes + 4
    const char* victim;    // 0x7f..a8        8 bytes --> largest number
    char respirate;        // 0x7f..b0        1 + 1
    short advantageous;    // 0x7f..b2
    int rodent;            // 0x7f..b4
    int sneezy;            // 0x7f..b8
};
char initiation; // [Data-BSS]  [0x600190]
int initiate=0;  // [Data]      [0x600070]
int main(int argc, char* argv[]){
    const char initiatory = 'V';      // [Data] [0x7f..f0]
    static int initiate = 200;        // [Data]     [0x600074]
    static int uninitialized;         // [Data-BSS] [0x600198]
    int initiator; // [Stack] auto varibles for main(), 4 bytes
    
    /**
     *  inject                  -> [Stack] env-argv-argc, a stack array
        "inject-gasoline-into"  -> [Stack] value of each elements in array
            [0x7f..a0|'i']      => [ &inject      | *inject      ]
            [0x7f..a1|'n']         [ &(inject+1)  | *(inject+1)  ]
            [0x7f..a2|'j']
                  ...
            [0x7f..a21|'\0']       [ &(inject+21) | *(inject+21) ]
        injectable              -> [Stack]  [0x7f..a22|0x7f..a0]
            
     */
    char inject[] = "inject-gasoline-into"; [Stacks] a bunch of stack
    inject++;    // Err: lvalue required
    char *injectable = inject;  // ptr to stack ,shouldn't delete
    injectable += 2;  // [0x7f..a22|0x7f..a2]
    *(injectable) = 'S'; // modify 'j' to 'S'
    printf("%s", inject);   // "inject-gasoline-into"
    printf("%s", injectable);   // "Sect-gasoline-into"
    
   
    /**
     *  injure          -> [Stack]  [0x7f..a0|&'i' in [Data]]
        "injure-injury" -> [Data]
         [0x7f..a0|0x..00]      =>      &injure
         [Data]                         NO Way to get addr. by injure
            [0x..00|'i']        =>      [ | *injure     ]
            [0x..01|'n']                [ | *(injure+1) ]
            
     */
    const char *injure = "injure-injury";   // ptr to [Data], needn't delete
    *(injure) = 'V';   // Err: 'const char' unmodifiable
    injure++;   // [0x7f..a0|0x..01]
    printf("%p %s %c", &injure, injure, *injure); // 0x7f..a0 "njure-injury" 'n'
    
    
    
    
    /**
     *  injector           -> [Stack]   [0x7f..a0|]
        reinterpret_cast<char *>malloc(3) -> [Heap] malloc()
     */
    char *injector;   // same as  "char *injector = 0;"
    injector = (char *)(malloc(3));   // allocate memory in heap, delete it
    *(injector) = 'V';
    *(injector+1) = 'i';
    *(injector+2) = '\0';
    printf("%s", injector); // Vi
    injector++;
    printf("%s", injector); // i
    delete injector; // Err: now injector is 'i', not addr. of the heap
    delete (--injector); // Ok, 
}  
