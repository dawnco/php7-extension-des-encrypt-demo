<?php

$src = "made in china";
$en_src = wumashi_password_encode('123456789');

echo "待加密字符串          : $src";
echo "\n";
echo "待加密字符串长度      : " . strlen($src);
echo "\n";
echo "加密后字符串base64后  : " . base64_encode($en_src);
echo "\n";
echo "加密后字符串长度      : " . strlen($src);
echo "\n";

//echo wumashi_password_decode("23");
