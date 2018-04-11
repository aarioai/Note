/**
 * PHP foreach
 */


/*
  $b = 1;
  $a[1][2] = $b;
 */

/**
 * @param op
 *  FETCH_DIM_W http://php.net/manual/en/internals2.opcodes.fetch-dim-w.php
 *    Fetch the value of the element at "index" in "array-value" to store it in "result".  Write-only
 */
filename:       /usr/_www/htdocs/index.php
function name:  (null)
number of ops:  7
compiled vars:  !0 = $b, !1 = $a
line  #* E I O op     fetch  ext  return  operands
-------------------------------------------------------------------------------------
2     0  E >   EXT_STMT
      1        ASSIGN                     !0, 1     // $b = 1
3     2        EXT_STMT
      3        FETCH_DIM_W        $1      !1, 1     // $1 = $a[1]
      4        ASSIGN_DIM                 $1, 2     // assign OP_DATA $a's index to 2
      5        OP_DATA                    !0, $3    // set current index(equal 2) of OP_DATA to $b
      6      > RETURN                     1




/*
    $a = ['Aaron', 'Script', '!'];
    foreach($a as $k=>$v){
      $a[$k+5] = $v;
      unset($a[$k]);
    }
    var_dump($a);
 */
unticked_statement:
  | T_FOREACH '(' variable T_AS {
      /**
       * zend_do_foreach_begin("foreach", '(', $arr, "as", 1 TSRMLS_CC)
       * @note to opcode
       *  FE_RESET reset the array pointer to the first element
       *  FE_FETCH
       */
      zend_do_foreach_begin(&$1, &$2, &$3, &$4, 1 TSRMLS_CC);
     }
     foreach_variable foreach_optional_arg ')' {
       /**
        * zend_do_foreach_cont("foreach", '(', "as", $k, $v TSRMLS_CC)
        * @note to opcode
        *
        */
       zend_do_foreach_cont(&$1, &$2, &$4, &$6, &$7 TSRMLS_CC);
     }
     foreach_statement {
       //zend_do_foreach_end("foreach", "as")
       zend_do_foreach_end(&$1, &$4 TSRMLS_CC);
     }

  | T_FOREACH '(' expr_without_variable T_AS {
      zend_do_foreach_begin(&$1, &$2, &$3, &$4, 0 TSRMLS_CC);
      }
     variable foreach_optional_arg ')' {
       zend_check_writable_variable(&$6);
       zend_do_foreach_cont(&$1, &$2, &$4, &$6, &$7 TSRMLS_CC);
     }
     foreach_statement {
       zend_do_foreach_end(&$1, &$4 TSRMLS_CC);
     }
     ;
/*
 ********************************The OPCODE***********************
 * @param op @see http://php.net/manual/en/internals2.opcodes.php
 *  FE_RESET http://php.net/manual/en/internals2.opcodes.fe-reset.php
 *    Initialize an iterator on array-value.  If the array is empty, jump to address.  
 *    Followed by FE_FETCH.
 *  FE_FETCH http://php.net/manual/en/internals2.opcodes.fe-fetch.php
 *    Fetch an element from iterator.  If no element is available, jump to address.  
 *    Followed by OP_DATA
 *  CONCAT http://php.net/manual/en/internals2.opcodes.concat.php
 *    Concats string values string1 and string2
 * @param int ext 
 * @operands array operand1[, operand2]
 *  operand1 the param to opcode
 *  operand2 if error
 * @note operand number: op_type symbol + union(int)
 *  op_type(symbol)
 *    IS_CONST
 *    IS_TMP_VAR(~)    e.g. ~5
 *    IS_VAR($)        e.g. $2
 *    IS_UNUSED
 *    IS_CV(!) cached value, union is an address  e.g. !0
 ******************************************************************
 filename:       /usr/_www/htdocs/index.php
 function name:  (null)
 number of ops:  25
 compiled vars:  !0 = $a, !1 = $k, !2 = $v
 line #* E I O op               fetch ext  return  operands
 -------------------------------------------------------------------------------------
 2    0  E >   EXT_STMT
      1        INIT_ARRAY                  ~0      'Aaron'
      2        ADD_ARRAY_ELEMENT           ~0      'Script'
      3        ADD_ARRAY_ELEMENT           ~0      '%21'
      4        ASSIGN                              !0, ~0     // assign ~0 to !0
 4    5        EXT_STMT
      6      > FE_RESET                    $2      !0, ->18   // reset !0 to the first element; on error jump to #18
      7    > > FE_FETCH                    $3      $2, ->18   // fetch $2 to $3; on error jump to #18
      8    >   OP_DATA                     ~5
      9        ASSIGN                              !2, $3     // $v = $3
      10       ASSIGN                              !1, ~5     // $k = ~5
 5    11       EXT_STMT
      12       ADD                         ~7      !1, 5      // ~7 = 5 + $k
      13       ASSIGN_DIM                          !0, ~7     // assign OP_DATA $a's index to ~7
                                                              // note: this index will be set to $a, but the loop is FE_FETCH $2
                                                              // $2 is assigned by ~0, it has no matter with $a any more
      14       OP_DATA                             !2, $9     // set current index (~7) of OP_DATA $a to $v, $a[5+$k] = $v;
 6    15       EXT_STMT
      16       UNSET_DIM                           !0, !1     // unset($a[$k])
 7    17      >JMP                                 ->7
      18    >  SWITCH_FREE                         $2
 9    19       EXT_STMT
      20       EXT_FCALL_BEGIN
      21       SEND_VAR                            !0
      22       DO_FCALL                 1          'var_dump'
      23       EXT_FCALL_END
      24      >RETURN                              1

 */
