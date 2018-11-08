### PHP7.2 扩展 加密演示


需要多个源文件,需要修改 config.m4
下面的需要 desc.c, 用 空格隔开
```
  PHP_NEW_EXTENSION(wumashi_password, wumashi_password.c des.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
```
