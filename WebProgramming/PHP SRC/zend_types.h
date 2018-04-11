typedef struct _zend_refcounted_h {
  uint32_t    refcount;
  union {
    struct {
      ZEND_ENDIAN_LOHI_3(zend_uchar type, zend_uchar flags, uint16_t gc_info)
    } v;
    uint32_t type_info;
  } u;
} zend_refcounted_h;

typedef struct {
  zend_refcounted_n gc;        // size = sizeof(uint32_t) =  1/2 * sizeof()
  zend_ulong        h;          // uint32_t
  size_type         len;        // memory after this struct
  char              val[1];
} zend_string;

static zend_always_inline zend_string *zend_string_init(const char *str, size_t len, int persistent) {
  zend_string *ret = zend_string_alloc(len, persistent);
  memcpy(ZSTR_VAL(ret), str, len);          // (zstr)->val
  ZSTR_VAL(ret)[len] = '\0';
  return ret;
}

static zend_always_inline zend_string *zend_string_alloc(size_t len, int persistent) {
  
  // _ZSTR_STRUCT_SIZE(len)  = aligned(sizeof (zend_string->val)) + len + 1 = sizeof(zend_string.zend_ulong) + len + 1
  // aligin with Z_L(8)  -> ulong
  zend_string *ret = (zend_string *)permalloc(ZEND_MM_ALIGNED_SIZE(_ZSTR_STRUCT_SIZE(len)), persistent);
  CG_REFCOUNT(ret) = 1;                 // ret->gc.refcount = 1
  GC_TYPE_INFO(ret) = IS_STRING | ((persistent ? IS_STR_PERSISTENT : 0) << 8);
  zend_string_forget_hash_val(ret);     // ret->h = 0;
	ZSTR_LEN(ret) = len;                  // ret->len = len
	return ret;
}


#define ZEND_MM_ALIGNED_SIZE(size) ((size + ZEND_MM_ALIGNMENT - Z_L(1)) & ZEND_MM_ALIGNMENT_MASK)
#define ZEND_MM_ALIGNMENT Z_L(8)
#define Z_L(i) INT64_C(i)

#define ZEND_MM_ALIGNMENT_MASK ~(ZEND_MM_ALIGNMENT - Z_L(1))


#define RETURN_STR(s) { RETVAL_STR(s); return; }
#define RETVAL_STR(s) ZVAL_STR(return_value, s)
#define ZVAL_STR(z, s) do {       \
  zval *__z = (z);                \
  zend_string *__s = (s);         \
  Z_STR_P(__z) = __s;             \
  Z_TYPE_INFO_P(__z) = ZSTR_IS_INTERNED(__s) ? IS_INTERNED_STRING_EX : IS_STRING_EX;    \
} while (0)
  


  
  
  
#define RETURN_STRING(s) {RETVAL_STRING(s); return; }
#define RETVAL_STRING(s) ZVAL_STRING(return_value, s)
#define ZVAL_STRING(z, s) do {          \
  const char *_s = (s);                 \
  ZVAL_STRINGL(z, _s, strlen(_s));      \
} while (0)
#define ZVAL_STRINGL(z, s, l) do {                \
  ZVAL_NEW_STR(z, zend_string_init(s, l, 0));     \
} while (0)
#define ZVAL_NEW_STR(z, s) do {           \
  zval *__z = (z);                        \
  zend_string *__s = (s);                 \
  Z_STR_P(__z) = __s;                     \
  Z_TYPE_INFO_P(__z) = IS_STRING_EX;      \
} while (0) 
  
  

#define Z_TYPE_INFO_P(zval_p) Z_TYPE_INFO(*zval_p)
#define Z_TYPE_INFO(zval) (zval).u1.type info
#define ZSTR_IS_INTERNED(s) (CG_FLAGS(s) & IS_STR_INTERNED)
#define CGFLAGS(p) (p)->gc.u.v.flags
#define IS_STR_INTERNED (1<<1)
#define IS_INTERNED_STRING_EX IS_STRING
#define IS_STRING_EX (IS_STRING | (( IS_TYPE_REFCOUNTED | IS_TYPE_COPYABLE) << Z_TYPE_FLAGS_SHIFT))

   






