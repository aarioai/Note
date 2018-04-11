<?php

$arr = ['name' => 'Aario', 'gender' => 'male'];
key($arr)      // 'name'
current($arr)  // 'Aario'

next($arr);
key($arr)     	// 'gender'
current($arr)  	// 'male



/**
 * @param $pad_type
 *  STR_PAD_RIGHT
 *  STR_PAD_LEFT
 *  STR_PAD_BOTH
 */
string str_pad($str, $pad_len[, $pad_str = ' '[, $pad_type = STR_PAD_RIGHT]])

/**
 * @example
 *  ltrim(class, '\\')
 */
string ltrim(string $str, string $trim = " \t\n\r\0\x0B")

/**
 * Compare two case-insensitive string
 * @return int 0 on equal; 
 */
int strcasecmp($str1, $str2)





/**
 * Extract [k=>v] to $prefixk = $v
 * @param int $extract_type
 *  EXTR_OVERWRITE
 *  EXTR_SKIP
 *  EXTR_PREFIX_SAME
 *  EXTR_PREFIX_ALL
 *  EXTR_PREFIX_INVALID
 *  EXTR_IF_EXISTS
 *  EXTR_REFS
 * @return int the number of variables successfully extracted
 */
int extract(&$arr, int $extract_type = EXTR_OVERWRITE, string $prefix = NULL)

/**
 * Like above, list [v] to $var1 = $v[0] ...
 */
list($var1[, $var2..]) = $arr







$arr = [1,2,3,4,5];
/**
 * @see http://php.net/manual/en/function.current.php
 */
mixed current(array &$arr)
mixed next(array &$arr)
mixed prev(array &$arr)
mixed end(array &$arr)
/**
 * @return $arr[0]
 */
mixed reset(array &$arr)
/**
 * Return then to next()
 * @return 
 */
array each(array &$arr)
while(list($k, $v) = each($arr)){}


arrlen_int_t array_unshift(array &$arr, $var1[, $val2[, $val3...]])
[index=>v] array_values([k=>v])
[v=>k] array_flip([k=>v])