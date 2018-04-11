class Contraception {
    char * fertilization = new char[1024];   // delete [] fertilization;
};


Contraception *c = new Contraception;   // delete c;
/*
HEAP SUMMARY:  1,032 bytes in 2 block
    total heal usage: 2 allocs, 0 frees, 1032 bytes allocated
    --> new Contraception   ==> 8 bytes
    --> new char[1024]  ==> 1024 * sizeof(char) bytes
LEAK SUMMARY:
    definitely lost: 8 bytes in 1 blocks
    indirectly lost: 1,024 bytes in 1 blocks
 */



/*****************************************************************************/ 






char *aspect = new char[4];                     //    delete [] aspect;
char *asperse = new char;                        //    delete asperse;


int *a = new int[4] {2,4,6,8};                  //    delete [] a;
int *pi = new int{6};  // *pi set to 6            //    delete pi;
    
   
int *pi = new int;
//invokes
int *pi = new(sizeof(int));


int *pa = new int[40];
// invokes
int *pa = new (40 * sizeof(int));


delete pi;
// translate to 
delete (pi);



char buffer[215];  // pointer-to-char, use (void *) cast, address is static 00FD9138
int *p1,  *p11, *p12, *p2, *p22, *p3;
p1 = new int[2]; // use heap, memory address is p1
p2 = new (buffer) int[2];  // invokes new (2 * sizeof(int), buffer)
 // use buffer array, place int array in buffer, memory address is (void *) buffer, int's adress is 00FD9138 and 00FD9140...

p11 = new int[2];  // each int has different address with p1
p22 = new (buffer) int[3];  // each int has the same address with p2, 00FD9138 00FD9140 and 00FD9148

int x = 1;
p3 = new (buffer + x * sizeof(int)) int[2];  // use from xth memories of buffer
// it'll use memories after the first one(00FD9138), which means 00FD9140 and 00FD9148, 
    
    
delete [] p1;
p12 = new int[2];  //use the same memory as p1

/**
  * The memory specified by buffer is static memory, and delete can be used 
  * only with a pointer to heap memory allocated by regu-lar new.
  * That is,the buffer array is outside the jurisdiction of delete,
  * and the following statement will produce a runtime error: 
  */
delete [] p2; // runtime error
    
/* 
On the other hand,if you use regular new to create a buffer in the first place,you use
regular delete to free that entire block.
 */
 
 delete [] p3;  // ok
 
 
 
 
 
 
/*
    If you use new to initialize a pointer member in a constructor,you should use delete in the destructor.
    The uses of new and delete should be compatible.You should pair new with delete and new [] with delete [].
    If there are multiple constructors,all should use new the same way—either all with brackets or all without brackets.There’s only one destructor,so all constructors have to be compatible with that destructor.However,it is permissible to initialize a pointer with new in one constructor and with the null pointer (0,or,with C++11, nullptr) in another constructor because it’s okay to apply the delete operation (with or without brackets) to the null pointer. */
    