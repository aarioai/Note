/*******************************************************************************
 *
    printf()
        %p  =  address
        %d  =  digit(int)               %u  =  usigned int
        %s  =  string                   %c  =  char
        %f  =  float                    %e  =  float in exponential format
        %g  =  the shorter one in length between %e and %f
        %x  =  hexadecimal int          %o  =  octal int
        %lu =  32-bit unsigned int      %llu=  64-bit unsigned int
        
 * DON'T USE "cout <<" to print address, otherwise, you'll get lost.
 * Cast "& char" to "(void *)&char" to print its address, otherwise it'll print 
    a pointer "char * rarely = &char"
    Notice: String
        cout << &char;          ===>    printf("%s", &char);
        cout << (void *)&char   ===>    printf("%p", &char);
 */
const char* essential = "colonial";
char colony = *essential;
cout << &colony;  // c▒     @, Damn it! it's pointer-like, but not an address!
cout << (void *)&colony;  // it's the address 'c' in "colonial";

printf("&s", &colony);  // c▒      @
printf("%p", &colony);  // same as "cout << (void *)&char"

/******************************************************************************/