
void master_thread(){
  goto loop;
  loop:
  
  for(int i=0; i<10; ++i){
    /**
     * Every Second
     *  flush log buffer to disk
     *  merge at most (innodb_io_capacity * 5%) insert buffers when IO is not busy
     *  flush innodb_io_capacity dirty pages when it's out of innodb_max_dirty_pages_pct
     *  go to background loop when no user activity
     */
    thread_sleep(1);      // sleep 1 second
    do_flush_log_buffer_to_disk();
    if(last_second_io_operations < (innodb_io_capacity * 5%))
      do_merge_at_most_X_insert_buffers // X = innodb_io_capacity * 5%
    if(buf_get_modified_ratio_pct > innodb_max_dirty_pages_pct)
      do_flush_X_dirty_pages(); // X = innodb_io_capacity
    if(no_user_activity)
      goto background loop;
  }
  
  /**
   * After 10s (ten one second):
   *  flush innodb_io_capacity dirty pages when IO operation is not busy in last ten seconds
   *  merge at most (innodb_io_capacity * 5%) insert buffers when IO is not busy
   *  flush log buffer to disk
   *  delete undo pages by full purge
   *  flush innodb_io_capacity or (10% * innodb_io_capacity) dirty pages
   */
  if(last_ten_seconds_io_operations < innodb_io_capacity)
    do_flush_X_dirty_pages();           // X = innodb_io_capacity
  do_merge_at_most_X_insert_buffers();  // X = innodb_io_capacity * 5%
  do_flush_log_buffer_to_disk();
  do_full_purge();
  if(buf_get_modified_ratio_pct > innodb_max_dirty_pages_pct)
    do_flush_X_dirty_pages();         // X = innodb_io_capacity
  else
    do_flush_X_dirty_pages();        // X = innodb_io_capacity * 10%
  goto loop;
  
  background loop:
  
  do_full_purge();
  merge_X_insert_buffers();        // X = innodb_io_capacity * 20%
  if(not_idle)
    goto loop:
  else
    goto flush loop;
    
  flush loop:
  
  do_flush_X_dirty_pages();       // X = innodb_io_capacity
  if(buf_get_modified_ratio_pct > innodb_max_dirty_pages_pct)
    goto flush loop;
  goto suspend loop
    
  suspend loop:
  
  suspend_thread();
  waiting_for_event();
  goto loop;
}