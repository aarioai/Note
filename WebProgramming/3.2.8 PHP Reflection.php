<?php
/**
 *@see http://php.net/manual/zh/class.reflection.php
 */
interface Reflector{
    public static export();
    public static __toString();
}

abstract class Reflection{
    public static export(Reflector $reflector, $return = false);
    public static getModifierNames(int $modifiers);
}

/**
 *@see http://php.net/manual/en/class.reflectionclass.php
 */
class ReflectionClass implements Reflector{
     
}

/**
 *@see http://php.net/manual/zh/class.reflectionproperty.php
 */
class ReflectionProperty implements Reflector{
    
}

/**
 *@see http://php.net/manual/zh/class.reflectionobject.php
 */
class ReflectionObject extends ReflectionClass implements Reflector{
    
}