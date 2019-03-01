# UUID in MySQL
## System UUID()
```
db> SELECT UUID()    // 233da027-0baf-11e6-929b-0242ac110004
```
## Bigint UUID at Instagram
[Sharding & IDs at Instagram](http://instagram-engineering.tumblr.com/post/10853187575/sharding-ids-at-instagram)
```sql
SET GLOBAL LOG_BIN_TRUST_FUNCTION_CREATORS=TRUE;
DELIMITER $$
DROP FUNCTION IF EXISTS aa_test.next_id;
CREATE FUNCTION aa_test.next_id(shard_id INT) RETURNS BIGINT
BEGIN
	DECLARE result BIGINT;
  DECLARE our_epoch BIGINT DEFAULT 1461675731970;
  DECLARE seq_id BIGINT;
  DECLARE now_millis BIGINT;
  INSERT INTO aa_test.uuid_key (id) VALUES (NULL);
  SELECT LAST_INSERT_ID() % 1024 INTO seq_id;
  SELECT FLOOR(UNIX_TIMESTAMP(SYSDATE(6)) * 1000) INTO now_millis;
  SET result = (now_millis - our_epoch) << 23;
  SET result = result | (shard_id << 10);
  SET result = result | (seq_id);
  RETURN result;
END 
$$
DELIMITER ;



CREATE TABLE aario.our_table (
  "id" bigint NOT NULL DEFAULT aario.next_id(5),   // 1236946587826000897
  ...rest of table schema...
)
```