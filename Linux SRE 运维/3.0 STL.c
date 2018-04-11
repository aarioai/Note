/**
 * Byte Manipulation[mə'nɪpjəleɪʃn]
 */
#include <string.h>
/**
 * byte zero
 * void bzero(void *dest, size_t nbytes);
 */
void * memset(void * dest, int c, size_t nbytes)

/**
 * void bcopy(const void *src, void *dest, size_t nbytes)
 */
void *memcpy(void * dest, const void *src, size_t nbytes);

/**
 * int bcmp(const void *ptr1, const void *ptr12, size_t nbytes);
 * @return int 0 if equal, nonzero if unequal
 */
int memcmp(const void *ptr1, const void *ptr2, size_t nbytes);