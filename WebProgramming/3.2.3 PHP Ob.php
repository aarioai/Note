<?php
ob_start();
echo 'Fag';
  $buf1 = ob_get_contents();  // 'Fag'
echo 'Fagot';
  $buf2 = ob_get_contents();  // 'FagFagot';
ob_end_clean();
ob_start();
ob_end_cleanr(); 
 
 


/**
 * @return 1 on already ob_start(); 0 on not yet, do ob_start()
 *  if(ob_get_level() == 0) ob_start();
 */
int ob_get_level() 
/**
 * @see http://php.net/manual/en/function.ob-start.php
 * @note Output buffers are stackable, that is, you may call ob_start() while 
 *  another ob_start() is active. Just make sure that you call ob_end_flush() 
 *  the appropriate number of times. If multiple output callback functions are 
 *  active, output is being filtered sequentially through each of them in 
 *  nesting order.
 */
bool ob_start([func_str(ob_get_contents())])
string|false ob_get_contents()
flush()
ob_flush()  // send the ob_get_contents() output buffer, but not destroy
ob_implicit_flush([int $on_off = true]): $on_off && flush();

bool ob_end_flush()
string ob_get_flush():= ob_end_flush()

ob_end_clean():= ob_get_level() = 0;

string ob_get_clean():= ob_get_contents() && ob_end_clean()