### PHP7.2 扩展 加密演示


需要多个源文件,需要修改 config.m4
下面的需要 desc.c, 用 空格隔开
```
  PHP_NEW_EXTENSION(wumashi_password, wumashi_password.c des.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
```

des 源码来自  https://github.com/tarequeh/DES/
密钥在 wumashi_password.c 文件里

```
//8位长度
static const unsigned char DES_KEY[] = "12345678";
```


### 安装方式
```
phpize
./configure
make && make install
```
php.ini 里填加 添加扩展
```
extension=wumashi_password.so
```

测试
```
php test.php
```

