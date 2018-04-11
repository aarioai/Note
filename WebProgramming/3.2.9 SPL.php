<?php
/**
 * http://php.net/manual/en/class.traversable.php
SPL提供了6个迭代器接口：
Traversable	遍历接口（检测一个类是否可以使用 foreach 进行遍历的接口）
Iterator	迭代器接口（可在内部迭代自己的外部迭代器或类的接口）
IteratorAggregate	聚合式迭代器接口（创建外部迭代器的接口）
Generator
OuterIterator	迭代器嵌套接口（将一个或多个迭代器包裹在另一个迭代器中）
RecursiveIterator	递归迭代访问接口（提供递归访问功能）
SeekableIterator	可索引迭代访问接口（实现查找功能）
 */

interface Traversable{
}

interface ArrayAccess extends \Traversable{
    public function offsetExists($offset);
    public function offsetGet($offset);
    public function offsetSet($offset, $value);
    public function offsetUnset($offset);
}
interface Iterator extends Traversable{
    public function current();
    public function key();
    public function next();
    public function rewind();
    public function valid();
}


interface Serializable{
    public function serialize();
    public function unserialize();
}
