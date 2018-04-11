/**
 * Any a device will output only when:
 *  1. end with a \n ( by press Enter)
 *  2. the full of its buffer
 *  3. by fflush() or flush()
 * @note stdout stdin are all devices, but stderr is not! stderr has no buffer, 
 *  it'll output always
 */


/**
 * All the data'll be buffed in stdout buffer. It'll be blocked for 2 seconds, 
 *  then output AbashBeehiveCreep in one lump sum
 */
fputs("Abash", stdout);     // not end with a \n
sleep(1);
printf("Beehive");          // not end with a \n
sleep(1);
printf("Creep");            // not end with a \n

/**
 * Abash  --1s-- Beehive --1s-- Creep
 */
printf("Abash\n");
sleep(1);
printf("Beehive\n");
sleep(1);
printf("Creep\n");

/**
 * With fflush() to flush the buffer and output without blocking
 */
printf("Abash");
sleep(1);
fflush(stdout);                   // flush stdout, output everything in buffer
fputs("Beehave", stdout);
fflush(stdout);
sleep(1);
fputs("Creep", stdout);


/**
 * Buffing in stdout, but not stderr. it'll output 
 *  ***ERR***(1s)***ERR***(1s)***ERR***(1s)***ERR***(1s)***ERR***(1s)***ERR***
 *  >>>OUT>>>>>>OUT>>>>>>OUT>>>>>>OUT>>>>>>OUT>>>>>>OUT>>>>>>OUT>>>
 */
while(1){
  fputs("***ERR***", stderr);
  fputs(">>>OUT>>>", stdout);
  sleep(1);
}