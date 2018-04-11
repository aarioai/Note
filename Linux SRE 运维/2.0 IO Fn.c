#include <unistd.h>
/**
 * @note
 *  0 STDIN_FILEDNO fileno(stdin)   standard input
 *  1 STDOUT_FILENO fileno(stdout)  standard output
 *  2 STDERR_FILENO fileno(stderr)  standard error output
 *    normally stderr has no buffer, it'll output message without blocking. But
 *    sometimes stderr is same as stdout, then it has buffer.
 */
int fileno(FILE * fileptr)

/**
 * @param const char *mode
 *  r open a file for reading
 *  w open a file for writing
 *  a open a file for writing at the end of file
 *  r+/w+ open a file for update; w+ will create the file if it does not exist
 *  a+ open a file for update at end of file
 * @example
 *  FILE *fpin = fdopen(connfd, "r");   // read from sockfd
 *    while(fgets(buf, sizeof(buf), fpin));
 *  FILE *fpout = fdopen(connfd, "w");
 *    fputs(buf, fpout);
 */
FILE * fdopen(int fd, const char *mode)


/**
 * Open a file or device
 * @param int flags
 *    O_NONBLOCK
 *    O_APPEND
 *    O_ASYNC
 *    O_DIRECT
 *    O_NOATIME
 *    O_RDONLY
 *    O_WRONLY
 *    O_RDWR
 *    O_CREAT
 *    O_EXCL
 *    O_NOCTTY
 *    O_TRUNC
 * @return int a file descriptor
 */
int open(const char *path, int flags)

/**
 * File-descriptor control
 * @param int cmd
 *  F_GETFD()  /  F_SETFD(int)      file descriptor flags
 *  F_GETFL()  /  F_SETFL(int)      file status flags
 * @see open()
 */
int fcntl(int fd, int cmd, ...)





/**
 * Delete a file and possibly the file it refers to
 */
int unlink(const char *path);


/**
 * +---------------------------------------------------------------------------+
 * |                    |    fd(s)    |      optional
 * |---------------------------------------------------------------------------+
 * | read() write()     | any one     |  
 * | readv() writev()   | any more    |
 * | recv() send()      | sockfd one  | flags
 * | recvfrom() sendto()| sockfd one  | flags/peer addr
 * | recvmsg() sendmsg()| sockfd more | flags/peer addr/control info
 * +---------------------------------------------------------------------------+
 */

/**
 * Attempts to read bytes_of_buf from the file associated with handle, and places the 
 *  characters read into buf. If the file is opened using O_TEXT, it removes 
 *  carriage returns and detects the end of the file.
 * @example 
 *  char remind[100]; ...; read(connfd, remind, sizeof(remind));  
 * @example
 *  struct args{long arg1; long arg2};
 *  write(connfd, &args, sizeof(args));
 *  read(connfd, &args, sizeof(args));
 * @return >0 bytes be read; 0 on End-Of-File; -1 on error
 */
int read(int file_descriptor, void * buf, size_t bytes_of_buf)
int write(int fd, void * buf, size_t bytes_of_buf)

#include <sys/uio.h>
struct iovec{
    void *iov_base;   // starting address
    size_t iov_len;   // size of transfered buffer
};
/**
 * read() one or more
 * @return ssize_t number of bytes read; -1 on error
 */
ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
ssize_t writev(int fd, const struct iovec *iov, int iovcnt)


/**
 * Read chars from file_ptr and stores them into buf until (bytes_of_buf-1) or
 *  either a newline or the EOF is reached
 * @param FILE * file_ptr stdin can be used to read from the standard input.
 * @return char * buf on success; null ptr on error
 */
char *fgets(char *buf, int bytes_of_buf, FILE * file_ptr)
/**
 * @param FILE * file_ptr stdout can be used to output
 * @return >0 on success; EOF on error
 */
int fputs(const char *buf, FILE * file_ptr)
/**
 * @param FILE *stream NULL on all open output streams;
 * @example
 *  fputs("", stdout);  or printf("")
 *  fflush(stdout); //  flush stdout buffers ,and print all buffer out to stdout
 */
int fflush(FILE *stream)
int fprintf(FILE *stream, const char *format, ...)

/**
 * Read formatted data from string and stores them according to args
 * @example sscanf("Hello, @AaronWell 2015-10", "%s %s %ld-03", &arg1, &arg2)
 *  char arg1[] = "@AaronWell"; long int arg2 = 2015
 * @return >=0 on success, args successfully filled; EOF on failure
 */
int sscanf(const char *buf, const char * format, ...)

/**
 * Write formatted data to string
 * @example sprintf(buf, "Hello, %s %ld-%d", "@AaronWell", 2015, 03)
*   char buf[] = "Hello, @AaronWell 2015-03"; 
 * @return >=0 on success, args successfully wrote; <0 on failure
 */
int sprintf(char *buf, const char *format, ...)

/**
 * Write formatted output to sized buf
 * @return >0 wrote bytes; 0 on buf be NULL; <0 on error  
 */
int snprintf(char *buf, size_t n, const char * format, ...)

#include <stdarg.h>
/**
 * @example vprintf("%d %d", ap);
 */
int vprintf(const char *format, va_list ap)
int vfprintf(FILE *stream, const char *format, va_list ap)
int vsprintf(char *buf, const char *format, va_list ap)
int vsnprintf(char *buf, size_t n, const char *format, va_list)