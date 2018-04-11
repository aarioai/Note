<?php
$redis = new Redis();

/**
 * ::connect(string host[, int port = 6379, float timeout_sec, reserved = NULL, int retry_millisec]
 */
$redis->connect('lef_redis', 6379);

/**
 * ::auth(string passwd)
 */
echo $redis->ping();

$redis->set('name', 'Aaron');

// db> keys *
var_dump($redis->keys('*'));

echo $redis->get('name');

/**
 * Data Type
 *  Redis::REDIS_STRING
 *  Redis::REDIS_SET
 *  Redis::REDIS_LIST
 *  Redis::REDIS_ZSET
 *  Redis::REDIS_HASH
 *  Redis::REDIS_NOT_FOUND
 */
echo $redis->type('name');

$redis->lpush('db-list', 'Redis');
$redis->lpush('db-list', 'MySQL');
$redis->lpush('db-list', 'Memcached');
var_dump($redis->lrange('db-list', 0, 1);

