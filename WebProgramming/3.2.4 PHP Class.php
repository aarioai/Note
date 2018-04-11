<?php
/**
 * class
 * object
 * instantiate
 * method
 * property
 */


/**
 * static::  parent::  self::(will overwrite parent) 
 */
class Abase
{
  public function prissy(){
    return new self();    // Abase always, not its derived class
  }
  public function fervent(){
    return new static(); 
  }
}
class Backer extends Abase{}
$backer = new Backer;
$backer->prissy();  // new Abase()
$backer->fervent(); // new Backer()






mixed call_user_func(string $func[, mixed $arg1[, $arg2...]]):= $func($args)



int func_num_args()
mixed func_get_arg($arg_num)
array func_get_args()
/**
 * @see http://php.net/manual/en/function.get-class.php
 */
string get_class($obj = null)
string get_parent_class($obj = null)
/**
 * @see http://php.net/manual/en/function.get-called-class.php
 * @return string name of the called class; bool false on error
 */
string get_called_class()
bool method_exists($obj, $method_nm)
bool property_exists($class, $property)
bool class_exists($class_nm, $autoload = true)
bool interface_exists($interface_nm, $autoload = true)
bool function_exists($func_nm)
bool class_alias($original = null, $alias = null)



 
/**
 * supported variable type keywords
 *      array [CLASS]
 */
class Projectile{}
function fascination(array $fascinate, Projectile $vomitting){
    
}

/**
 * abstract class can extend another abstract class
 */ 
abstract class hell{}
abstract class heaven extends hell{} 
 
 
/**
 * assignment of class via reference, clone a class is copy-on-write
 * Using _clone() method
 */
$Nausea = new Nausea();
$Nausea->neuron = 'Nausea::neuron';
$Seasick = $Nausea;  // assign via reference
$Seasick->neuron = 'Seasick::neuron';
echo $Nausea->neuron;  // Seasick::neuron 
$Carsick = clone $Nausea;  // copy-on-wirte
$Carsick->neuron = 'Carsick::neuron';
echo $Nausea->neuron; // Seasick::neuron
 
 
 
/**
 * interface, abstract and instanceOf, polymorphic
 * 
 */
interface ParalysisIf{
} 
abstract class AnaemiaAb{
    public $property;
    public static $soleStatic;
    public static $overwrite;
}
class Bachelor extends AnaemiaAb implments ParalysisIf{
    public static $overwrite;
}
class Cage extends AnaemiaAb{
    public static $overwrite;
}
$AnaemiaAb = new AnaemiaAb(); // Error: NOT allowed


AnaemiaAb::$soleStatic = 'avian';
/* @ouput avian avian avian */
echo AnaemiaAb::$soleStatic, ' ', Bachelor::$soleStatic, ' ', Cage::$soleStatic;

Bachelor::$soleStatic = 'brutal';
/* @ouput brutal brutal brutal */
echo AnaemiaAb::$soleStatic, ' ', Bachelor::$soleStatic, ' ', Cage::$soleStatic;

Cage::$soleStatic = 'contagious';
/* @ouput contagious contagious contagious */
echo AnaemiaAb::$soleStatic, ' ', Bachelor::$soleStatic, ' ', Cage::$soleStatic;


AnaemiaAb::$overwrite = 'invade';
/* @ouput invade NULL NULL */
echo AnaemiaAb::$overwrite, ' ', Bachelor::$overwrite, ' ', Cage::$overwrite;

Bachelor::$overwrite = 'colony';
/* @ouput invade colony NULL */
echo AnaemiaAb::$overwrite, ' ', Bachelor::$overwrite, ' ', Cage::$overwrite;


// Polymorphic
$Bachelor = new Bachelor();
if($Bachelor instanceOf Bachelor){  // true
}
if($Bachelor instanceOf AnaemiaAb){  // true
}
if($Bachelor instanceOf ParalysisIf){  // true
}


/**
 * serialize
 */
$bachelor_sleep = serialize($Bachelor);  // string for saving (in DB/Disk)
$Bachelor_wakeup = unserialize($bachelor_sleep); // Object








