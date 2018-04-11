/**
 * @see https://github.com/laruence/php7-internal/blob/master/zval.md
 */
/* regular data types */
#define IS_UNDEF                    0

/**
 * these sizes are less than 16 (in 64-bit OS), a reference count is no need for
 *  the types below (null/false/true/long/double)
 * String Interning
 * @see https://en.wikipedia.org/wiki/String_interning
 *      http://stackoverflow.com/questions/10578984/what-is-string-interning
 *  
 */
#define IS_NULL                     1
#define IS_FALSE                    2
#define IS_TRUE                     3
#define IS_LONG                     4
#define IS_DOUBLE                   5


#define IS_STRING                   6
#define IS_ARRAY                    7
#define IS_OBJECT                   8
#define IS_RESOURCE                 9
#define IS_REFERENCE                10

/* constant expressions */
#define IS_CONSTANT                 11
#define IS_CONSTANT_AST             12

/* fake types */
#define _IS_BOOL                    13
#define IS_CALLABLE                 14

/* internal types */
#define IS_INDIRECT                 15
#define IS_PTR                      17 
 
struct _zval_struct {
  union {
    zend_long         lval;
    double            dval;
    zend_refcounted   *counted;
    zend_string       *str;
    zend_array        *arr;
    zend_object       *obj;
    zend_resource     *res;
    zend_ast_ref      *ast;
    zval              *zv;
    void              *ptr;
    zend_class_entry  *ce;
    zend_function     *func;
    struct {
      uint32_t w1;
      uint32_t w2;
    } ww;
  } value;
  
  union {
    struct {
      ZEND_ENDIAN_LOHI_4(
        zend_uchar  type,             /* active type */
        zend_uchar  type_flags,
        zend_uchar  const_flags,
        zend_uchar  reserved          /* call info for EX(This) */
      )
    } v;
    uint32_t type_info;
  } u1;
  
  union {
      uint32_t     next;                 /* hash collision chain */
      uint32_t     cache_slot;           /* literal cache slot */
      uint32_t     lineno;               /* line number (for ast nodes) */
      uint32_t     num_args;             /* arguments number for EX(This) */
      uint32_t     fe_pos;               /* foreach position */
      uint32_t     fe_iter_idx;          /* foreach iterator index */
  }
} 


/**
 * E.g. PHP Array
 */
typedef struct _zend_refcounted_h {
  uint32_t    refcount;
  union {
    struct {
      ZEND_ENDIAN_LOHI_3(
        zend_uchar  type,
        zend_uchar  flags,      /* for strings and objects */
        uint16_t    gc_info     /* */
      ) 
    } v;
    uinit32_t type_info;
  } u;
} zend_refcounted_h;
 