/** 
 * Blocking connect(): one connect() a time
 * Nonblocking connect()s : Web Client, multiple connect()s a time
 *  +--------------------------------------------------------------------------+
 *  |            -(connect()<0 && errno != EINPROGRESS)-> exit()
 *  | connect(1) -(connect()>=0)-> write(GET /1.jpg HTTP/1.1\r\n\r\n) --> read()
 *  |            -(errno == EINPROGRESS)->
 *  | ...
 *  | connect(n) -> write(GET /1.jpg HTTP/1.1\r\n\r\n)  -->   read()
 *  +--------------------------------------------------------------------------+
 * @notice When connect() a nonblocking socket to a different server, and the
 *  connection can't be established immediately. connect() returns immediately 
 *  with an errno EINPROGRESS but the TCP three-way handshake continues. 
 */

#include "sock.h"

/**
 * @example
 *  GET /index.html HTTP/1.1\r\n\r\n
 */
#define GET_HTTP1 "GET %s HTTP/1.1\r\n\r\n"


int main(){
  
  
}