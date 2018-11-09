<?php

function test($str){
	echo "\n";
	echo "\n";
	
	$en_str = wumashi_password_encode($str);
	echo "待加密字符串          : $str";
	echo "\n";
	echo "待加密字符串长度      : " . strlen($str);
	echo "\n";
	echo "加密后字符串base64后  : " . base64_encode($en_str);
	echo "\n";
	echo "加密后字符串长度      : " . strlen($en_str);
	echo "\n";
	echo "\n";
	
	$de_str = wumashi_password_decode($en_str);
	echo "待解密字符串base64后  : " . base64_encode($en_str);
	//echo "\n";
	//echo "待解密字符串长度      : " . strlen($en_str);
	echo "\n";
	echo "解密后字符串          : " . $de_str;
	echo "\n";
	echo "解密后字符串长度      : " . strlen($de_str);
	echo "\n";


}

test("12345678");
test("123456789");
test("1234567890");
test("1234567812345678");
test("12345678123456781");

