dnl $Id$
dnl config.m4 for extension module_sample

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(module_sample, for module_sample support,
dnl Make sure that the comment is aligned:
dnl [  --with-module_sample             Include module_sample support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(module_sample, whether to enable module_sample support,
dnl Make sure that the comment is aligned:
dnl [  --enable-module_sample           Enable module_sample support])

if test "$PHP_MODULE_SAMPLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-module_sample -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/module_sample.h"  # you most likely want to change this
  dnl if test -r $PHP_MODULE_SAMPLE/$SEARCH_FOR; then # path given as parameter
  dnl   MODULE_SAMPLE_DIR=$PHP_MODULE_SAMPLE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for module_sample files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MODULE_SAMPLE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MODULE_SAMPLE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the module_sample distribution])
  dnl fi

  dnl # --with-module_sample -> add include path
  dnl PHP_ADD_INCLUDE($MODULE_SAMPLE_DIR/include)

  dnl # --with-module_sample -> check for lib and symbol presence
  dnl LIBNAME=module_sample # you may want to change this
  dnl LIBSYMBOL=module_sample # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MODULE_SAMPLE_DIR/$PHP_LIBDIR, MODULE_SAMPLE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MODULE_SAMPLELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong module_sample lib version or lib not found])
  dnl ],[
  dnl   -L$MODULE_SAMPLE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MODULE_SAMPLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(module_sample, module_sample.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
