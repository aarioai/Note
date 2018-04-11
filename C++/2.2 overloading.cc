#include <stdarg.h>
#ifdef _M_ALPHA
  typedef struct {
    char *a0;   /* pointer to first homed integer argument */
    int offset; /* byte offset of next parameter */
  } va_list;
#else
  typedef char * va_list;
#endif
/**
 * Get the sizeof(n) that should be n times of sizeof(int)
 * @note int is 4-bit in CentOS 64-bit
 * @example _INTSIZEOF(char)
 *  (1+4-1)&~(4-1) = 4&~3 = 4&(-4) = 4
 * @exmple 
 *  struct fabric{int faeces; int urine; char pee;}  // 4 + 4 + 1 + padding = 12
 *  _INITSIZEOF(fabric)
 *  (12+4-1)&(-4) = 12
 */
#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )
/**
 * set ap to an offset (by _INTSIZEOF(v)) to the addr. of v
 */
#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )
/**
 * Get this arg's value with a type t. Befere do'ng this, move ap to next 
 *  _INTSIZE(t) ptr
 */
#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap) ( ap = (va_list)0 )


int sum(int add, ...) {
  int total = add;
  va_list ap;     // additional arguments
  va_start(ap, add);    // now ap is ptr to a offset of _INTSIZEOF(int) to &add
  /**
   * output
   *  0x7fffef9d3e0c(&add)
   *  0x7fffef9d3e10(va_list)
   */
  printf("%p(&add)\n%p(va_list)\n", &add, &ap);
  
  /**
   * If next argument is a char, e.g sum(100, 'A') then get 'A' by
   */
 /// char fang = *((char *)ap)
  vprintf("%d %d %d", ap);      // printf  arg2 arg3 arg4
  char buf[100];
  vsprintf(buf, "%d %d %d", ap);
  printf("%s", buf);
  total += va_arg(ap, int);   
  total += va_arg(ap, int);
  
  va_end(ap);
}


void x(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  while (*format++) {
    switch (*format) {
    case 's':   // string
      printf("%s", va_arg(ap, char *));
      break;
    case 'd':
      break;
    case 'c':
      break;
    }
  }
}
