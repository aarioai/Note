

#define emalloc(size)						_emalloc((size) ZEND_FILE_LINE_CC ZEND_FILE_LINE_EMPTY_CC)
#define efree(ptr)							_efree((ptr) ZEND_FILE_LINE_CC ZEND_FILE_LINE_EMPTY_CC)

# define _emalloc(size) (__builtin_constant_p(size) ? ZEND_ALLOCATOR(size) : _emalloc(size))
# define ZEND_ALLOCATOR(size) ZEND_MM_BINS_INFO(_ZEND_BIN_ALLOCATOR_SELECTOR_START, size, y) \
  ((size <= ZEND_MM_MAX_LARGE_SIZE) ? _emalloc_large(size) : _emalloc_huge(size))   \ ZEND_MM_BINS_INFO(_ZEND_BIN_ALLOCATOR_SELECTOR_END, size, y)


#define ZEND_FILE_LINE_CC , ZEND_FILE_LINE_C
#define ZEND_FILE_LINE_C __FILE__, __LINE__


# define ZEND_FILE_LINE_EMPTY_CC , ZEND_FILE_LINE_EMPTY_C
# define ZEND_FILE_LINE_EMPTY_C NULL, 0





#define pemalloc(size, persistent) (persistent ? __zend_malloc(size) : emalloc(size))
#define pefree(ptr, persistent)  ((persistent)?free(ptr):efree(ptr))