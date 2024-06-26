dnl config.m4 for extension wumashi_password

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([wumashi_password],
dnl   [for wumashi_password support],
dnl   [AS_HELP_STRING([--with-wumashi_password],
dnl     [Include wumashi_password support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([wumashi_password],
  [whether to enable wumashi_password support],
  [AS_HELP_STRING([--enable-wumashi_password],
    [Enable wumashi_password support])],
  [no])

if test "$PHP_WUMASHI_PASSWORD" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, WUMASHI_PASSWORD_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-wumashi_password -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/wumashi_password.h"  # you most likely want to change this
  dnl if test -r $PHP_WUMASHI_PASSWORD/$SEARCH_FOR; then # path given as parameter
  dnl   WUMASHI_PASSWORD_DIR=$PHP_WUMASHI_PASSWORD
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for wumashi_password files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WUMASHI_PASSWORD_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WUMASHI_PASSWORD_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the wumashi_password distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-wumashi_password -> add include path
  dnl PHP_ADD_INCLUDE($WUMASHI_PASSWORD_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-wumashi_password -> check for lib and symbol presence
  dnl LIBNAME=WUMASHI_PASSWORD # you may want to change this
  dnl LIBSYMBOL=WUMASHI_PASSWORD # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_WUMASHI_PASSWORD_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your wumashi_password library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WUMASHI_PASSWORD_DIR/$PHP_LIBDIR, WUMASHI_PASSWORD_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_WUMASHI_PASSWORD_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your wumashi_password library.])
  dnl ],[
  dnl   -L$WUMASHI_PASSWORD_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(WUMASHI_PASSWORD_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_WUMASHI_PASSWORD, 1, [ Have wumashi_password support ])

  PHP_NEW_EXTENSION(wumashi_password, wumashi_password.c, $ext_shared)
fi
