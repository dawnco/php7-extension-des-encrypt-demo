/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_wumashi_password.h"

#include "des.h"
#include "ext/standard/base64.h"

/* If you declare any globals in php_wumashi_password.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(wumashi_password)
*/

/* True global resources - no need for thread safety here */
static int le_wumashi_password;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wumashi_password.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_wumashi_password_globals, wumashi_password_globals)
    STD_PHP_INI_ENTRY("wumashi_password.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_wumashi_password_globals, wumashi_password_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

//字符串截取
int substr(char *dst,char *src, int len, int start){
  char *p=dst;
  char *q=src;
  int length=strlen(src);
  if(start >= length||start<0) return -1;
  if(len > length) len=length-start;
  q+=start;
  while(len--)
  {
    *(p++)=*(q++);
  }
  return len;
}

//加密
PHPAPI zend_string *php_des_encode(unsigned char *str, size_t str_len){
	

    int i = 0;

	zend_string *result;
    unsigned char *p;
	
	unsigned char* data_block = (unsigned char*) emalloc(8*sizeof(char));
	unsigned char* processed_block = (unsigned char*) emalloc(8*sizeof(char));
	key_set* key_sets = (key_set*)emalloc(17*sizeof(key_set));
	
	
	
	unsigned short int padding;
	
	generate_sub_keys(DES_KEY, key_sets);
	
	//des 加密
	unsigned long block_count = 0, number_of_blocks;
	
	//区块数量
	number_of_blocks = str_len/8 + ((str_len%8)?1:0);

    result = zend_string_safe_alloc(number_of_blocks, 8 * sizeof(char), 0, 0);

    p = (unsigned char *)ZSTR_VAL(result);

	
	while(block_count < number_of_blocks){
		block_count ++;
		substr(data_block, str, 8, block_count * 8);
		
		if (block_count == number_of_blocks){
			//最后一块
			padding = 8 - str_len%8;
			if (padding < 8) { // Fill empty data block bytes with padding
				memset((data_block + 8 - padding), (unsigned char)padding, padding);
			}
			process_message(data_block, processed_block, key_sets, ENCRYPTION_MODE);
		}else{
            process_message(data_block, processed_block, key_sets, ENCRYPTION_MODE);
        }

        for (i= 0; i < 8; i++){
            *p++ = processed_block[i];
        }
		
	}

    *p = '\0';

    efree(data_block);
    efree(processed_block);
    efree(key_sets);


    ZSTR_LEN(result) = (p - (unsigned char *)ZSTR_VAL(result));
	return result;
}
   
   
/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_wumashi_password_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(wumashi_password_encode)
{
    char *str;
    size_t str_len;
    zend_string *result_des;
    zend_string *result;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, str_len)
    ZEND_PARSE_PARAMETERS_END();


    result_des = php_des_encode((unsigned char*)str, str_len);

    result = php_base64_encode((unsigned char*)result_des, strlen(result_des));
    if (result != NULL) {
        RETURN_STR(result);
    } else {
        RETURN_FALSE;
    }
}

PHP_FUNCTION(wumashi_password_decode)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;
	zend_string *result;
	
	zend_bool strict = 0;
	
	
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "wumashi_password_encode %s", arg);

		
	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_wumashi_password_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_wumashi_password_init_globals(zend_wumashi_password_globals *wumashi_password_globals)
{
	wumashi_password_globals->global_value = 0;
	wumashi_password_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(wumashi_password)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wumashi_password)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wumashi_password)
{
#if defined(COMPILE_DL_WUMASHI_PASSWORD) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(wumashi_password)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wumashi_password)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wumashi_password support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ wumashi_password_functions[]
 *
 * Every user visible function must have an entry in wumashi_password_functions[].
 */
const zend_function_entry wumashi_password_functions[] = {
	PHP_FE(wumashi_password_encode,	NULL)		/* For testing, remove later. */
	PHP_FE(wumashi_password_decode,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in wumashi_password_functions[] */
};
/* }}} */

/* {{{ wumashi_password_module_entry
 */
zend_module_entry wumashi_password_module_entry = {
	STANDARD_MODULE_HEADER,
	"wumashi_password",
	wumashi_password_functions,
	PHP_MINIT(wumashi_password),
	PHP_MSHUTDOWN(wumashi_password),
	PHP_RINIT(wumashi_password),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(wumashi_password),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(wumashi_password),
	PHP_WUMASHI_PASSWORD_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WUMASHI_PASSWORD
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wumashi_password)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
