/**
 * @return 
 *  RETURN_LONG(l)
 *  RETURN_BOOL(b)
 *  RETURN_TRUE
 *  RETURN_FALSE
 *  RETURN_NULL()
 *  RETURN_DOUBLE(d)
 *  RETURN_STRING(s, dup)
 *  RETURN_STRINGL(s, l, dup)       a string with length l
 *  RETURN_RESOURCE(r)
 */

PHP_FUNCTION()





/**
 * @param char *type_spec 
 *  l long
 *  d double
 *  s char*, int len
 *  b zend_bool
 *  r zval *
 *  a zval *
 *  o zval *
 *  O zval *
 *  z zval *
 */
zend_parse_parameters(int num_args TSRMLS_DC, char *type_spec, ...);
 
 
PHP_FUNCTION(confirm_module_sample_compiled) {
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;
  /**
   *  module_sample("Aario")
   */
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
    php_error(E_WARNING, "function module_sample(): not implemented yet");
	}
	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "module_sample", arg);
	RETURN_STRING(strg);
}


PHP_FUNCTION(confirm_module_sample_compiled) {
  int argc = ZEND_NUM_ARGS();
  long n;
  /**
   * module_sample(string, long)
   */
  zend_parse_parameters(argc TSRMLS_C, "sl", &arg, &arg_len, &n)
}