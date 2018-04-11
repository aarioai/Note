/**
 * size_t : unsigned long (64bit) / unsigned int (32 bit)
 */

/**
 * ./stipulate.out 100 200 300
 *  argc = 4
 *  *argv = ./stipulate.out
 *  *(argv+1) = 100
 *  *(argv+2) = 200
 *  *(argv+3) = 300
 */
int main(int argc, char **argv) {
    size_t id = fork();   // same as int id = fork();
    for(argc; argc > 0; --argc) {
        printf("%s", *(argv + argc - 1));
    }
}


/**
 * extern specifies that the external linkage or convertions of other language
    extern "C++" in C
    extern "C" in C++
 */
 
/******************************* extinct.h ************************************/
#pragma once            // #ifndef G_  #define G_  ... #endif
int lateral = 100;
extern int sourish; // external linkage
/******************************* Source.cpp ***********************************/
#include "extinct.h"
int sourish;
extern int lateral; // specifies that "int lateral" declared in another file
int main() {
    lateral = 200;
    return 0;
} 
/******************************* extinct.cpp **********************************/
#include "extinct.h"

/******************************************************************************/ 


extern "C" {   // with C linkage
    #include <stdio.h>
    void external(int internal);
}
extern "C" int exterior(bool interior);  // declare function with C linkage;
extern "C" int errno;  // declare a global variable with C linkage