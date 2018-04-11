#ifndef PHP_MODULE_SAMPLE_H
#define PHP_MODULE_SAMPLE_H

extern zend_module_entry module_sample_module_entry;
#define phpext_module_sample_ptr &module_sample_module_entry

#define PHP_MODULE_SAMPLE_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_MODULE_SAMPLE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_MODULE_SAMPLE_API __attribute__ ((visibility("default")))
#else
#	define PHP_MODULE_SAMPLE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define MODULE_SAMPLE_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(module_sample, v)

#if defined(ZTS) && defined(COMPILE_DL_MODULE_SAMPLE)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif