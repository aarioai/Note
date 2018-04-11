#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_module_sample.h"


static int le_module_sample;

PHP_FUNCTION(confirm_module_sample_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "module_sample", arg);

	RETURN_STR(strg);
}

PHP_MINIT_FUNCTION(module_sample)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(module_sample)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}

PHP_RINIT_FUNCTION(module_sample)
{
#if defined(COMPILE_DL_MODULE_SAMPLE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(module_sample)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(module_sample)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "module_sample support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}

const zend_function_entry module_sample_functions[] = {
	PHP_FE(confirm_module_sample_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in module_sample_functions[] */
};

zend_module_entry module_sample_module_entry = {
	STANDARD_MODULE_HEADER,
	"module_sample",
	module_sample_functions,
	PHP_MINIT(module_sample),
	PHP_MSHUTDOWN(module_sample),
	PHP_RINIT(module_sample),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(module_sample),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(module_sample),
	PHP_MODULE_SAMPLE_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_MODULE_SAMPLE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(module_sample)
#endif
