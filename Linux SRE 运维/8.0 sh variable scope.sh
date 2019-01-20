#!/bin/bash

readonly CONST=100
readonly CONST2=10
declare var
declare var2
declare var3

fn() {
	echo '	fn CONST='$CONST
	echo '	fn CONST2='$CONST2
	echo '	fn var='$var
	echo '	fn var2='$var2
	echo '	fn var3='$var3
	readonly CONST=9
	local CONST2=999
	readonly FN_CONST='const in function'
	local var=0
	declare var2='var2 after'
	declare fnvar='var in function'

	for var3 in {10..5}; do
		var=$var3
	done



	echo '	fn CONST='$CONST
	echo '	fn CONST2='$CONST2
	echo '	fn var='$var
	echo '	fn var2='$var2
	echo '	fn var3='$var3
	if [ 1 -eq 1 ]; then
		local bad='bad'
		echo $bad
	fi
}

echo '>>>CONST='$CONST
echo '>>>CONST2='$CONST2
echo '>>>var='$var
echo '>>>var2='$var2
echo '>>>var3='$var3
fn
echo '<<<CONST='$CONST
echo '<<<CONST2='$CONST2
echo '<<<var='$var
echo '<<<var2='$var2
echo '<<<var3='$var3

echo '------FN_CONST='$FN_CONST
echo '------fnvar='$fnvar
