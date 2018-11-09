### PHP7.2 扩展 加密演示



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


#### 说明

需要多个源文件,需要修改 config.m4
本扩展需要用到desc.c, 需要修改成如下, 用空格隔开 "wumashi_password.c des.c"
```
  PHP_NEW_EXTENSION(wumashi_password, wumashi_password.c des.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
```
