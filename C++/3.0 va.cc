extern "C" {
    #include <stdarg.h>
    static void vacant(int, int, const char *, ...);
    static void vacant(int vacate, int vacuity, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        printf(fmt, args);
        va_end(args);
    }
}