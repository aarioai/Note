<?php
ignore_user_abort(ture);    // ignore user close web, be used for log maker


bool is_array($var)
bool is_object($var)


/**
 * string __NAMESPACE__
 * string __CLASS__  : get current class name
 * string get_class([object $obj = NULL]) : get instance's class name
 * string __FUNCTION__
 * string __METHOD__
 * string __DIR__
 * string __FILE__
 * string __LINE__
 */

class Nonce
{
  public function __construct(){
    echo PHP_EOL,'<br> CONSTRUCT: ', get_class($this) , '<br>', PHP_EOL;
  }

  public static function getName(){
    return __CLASS__;
  }
  public static function getClassName(){
    return get_class();
  }
  public static function getCalledClassName(){
    return get_called_class();
  }
  public function __destruct(){
    echo PHP_EOL, '<br> DESTRUCT: ', get_class($this) , '<br>', PHP_EOL;
  }
}

class Arid extends Nonce
{

}

echo Arid::getName() , PHP_EOL;               // Nonce
echo Arid::getClassName() , PHP_EOL;          // Nonce
echo Arid::getCalledClassName() , PHP_EOL;    // Arid

$a = new Arid();                              // CONSTRUCT: Arid
echo $a::getName() , PHP_EOL;                 // Nonce
echo $a::getClassName() , PHP_EOL;            // Nonce
echo $a::getCalledClassName() , PHP_EOL;      // Arid
$a = null;                                    // DESTRUCT: Arid