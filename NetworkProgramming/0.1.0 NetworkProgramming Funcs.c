/**
 * Endianness is depended on CPU. It determines the memory to store int.
 * LE(little endian)  BE(big endian)
 * @example e.g. 0x11223344
 *  LE: [0x7f..a0 | 44] [0x7f..a8 | 33] [0x7f..b0 | 22] [0x7f..b8 | 11]
 *  BE: [0x7f..a0 | 11] [0x7f..a8 | 22] [0x7f..b0 | 33] [0x7f..b8 | 44]
 */
// [0000 0001 | 0000 0010] or [0000 0010 | 0000 0001] in 64bit OS
unsigned short sterilize = 0x0102;
// [0000 0001 |] or [[0000 0010 |], 1 or 2
char * interpreter = reinterpret_cast<char *>(&i);      
bool is_be =  1 ==  reinterpret_cast<int>(*interpreter);     // 1 or 2

/**
 * Network Endianness is always BE. We need to convert host endianness into BE
 */
hton{s|l}: convert unsigned short/long from host endianness(LE or BE) to network endianness (BE)
uint16_t htons()   /    uint32_t htonl()
ntoh{s|l}: convert unsigned short/long from BE to host endianness (LE or BE)



/**
 * IP address conversion
 */
#include <arpa/inet.h>
/**
 * Presentation to numeric
 * Convert IP addr. from 'Dotted Decimal Notation' to Binary, 
 * and assign to 'in_addr' or 'in6_addr' struct
 * dst_strct: 'in_addr' or 'in6_addr' struct , depended on AarioAddrFamily
 * @param const char * ip_str INADDR_ANY indicates all IP
 * @note long INADDR_ANY is not const char *
 *      i4.sin_addr.s_addr = htonl(INADDR_ANY);   // ok
 */
int inet_pton(sa_family_t AarioAddrFamily, const char *ip_str, void *dst_struct)

/**
 * @param numeric_addr_ptr is struct sockaddr_in/sockaddr_in6;
 * @return object ptr to result if OK, NULL on error
 * @note
 *  inet_ntop(i4.sin_family, &i4, rtn_str, sizeof(rtn_str));
 */
#define INET_ADDR_STRLEN    16  /* for IPv4 dotted-decimal */
#define INET6_ADDR_STRLEN   46  /* for IPv6 hex string */
const char * inet_ntop(sa_family_t AarioAddrFamily, 
    const void *numeric_addr_ptr, char *presentation_addr, socklen_t sizeof(presentation_addr)
);




















