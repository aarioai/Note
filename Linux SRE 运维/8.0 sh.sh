#!/bin/bash
# @see http://google.github.io/styleguide/shell.xml
# @see http://tiswww.case.edu/php/chet/bash/FAQ



########################## Stream #################################
read -p "Your Name:" -t 10 name
    -p "Hint: "     # hint
    -t 10           # 10 sec

########################## FILE ###################################
filename="$(pwd)/aario.cc"
if [ -f ${filename} -a ${filename##*.} ] then
  echo ${filename##*.}     # get the extension
fi

######################### STRING ##################################
echo "Hello, $name"
${name^^}       # uppercase()



######################### PROCESS #################################
rand=$RANDOM
bash            # create a child shell bash, and parent bash is sleeping
echo ${rand}    # nothing
exit            # back to parent process

export rand
bash
echo ${rand}    # e.g. 32767
unset ${rand}   # child process's ${rand} is unseted, not the parent's
exit

echo ${rand}    # e.g. 32767





extraneous=100
substitution=10
subsist=$(($(extraneous) + $(substitution)))
bitwiseOperate=$((3&7))
bitwiseOperate=$((3|7))
bitwiseOperate=$((3^7))
bitwiseOperate=$((3<<7))

i=0
i=$[ $i + 1 ]

appellation="Aario"   
appellation=100         # redefine, never quote literal integers

CONST_NUM = 1000
readonly CONST_NUM            # constant
unset CONST_NUM               # unset a variable
readonly semen="ovum"


declare [-aixr] VAR 
    -a array
    -i int
    -x 
    -r readonly
declare -i sum = $RANDOM*10/32768  # $RANDOM = [0, 32767]

declare -xr CONST_AND_ENV="extraneous" # both constant and environment

scores=(1 3 4 5)
scores[4]=8
echo ${scores[1]}

value=4

isInArray() {
    
}
isInArray2() {
    search=$1
    arr=$2
    search=${search,//\./\\.}
    search=${search,//\*/\\*}
    search=${search,//\+/\\+}
    search=${search,//\?/\\?}
    # ${v/replacement/replaceTo}
    if [ echo "${arr[@]}" | grep -E "(^$search,)|(,$search,)|(,$search$)"  ]; then 
        return 1
    fi
    return 0
}






source "./b.sh"   # run ./b.sh
. ./b.sh          # run ./b.sh

DATE=$(date)        # DATE=`date`   call system date command
USER=$(who | wc -l)
DATE_UPTIME=$(date; DATE_UPTIMEtime)

echo -e "\n"  # disable escape-char '\'
echo '\n'     # 
printf "\n"   # "\n"
printf "%d %s\n" 100 "Aaron"


test="I'm Aario Ai!"
# ${var/replacement/replace}         replace once
echo ${test/ /\\s}         #  I'm\sAario Ai!

# ${var//replacement/replace}       replace all
echo ${test// /\\s}        # I'm\sAario\sAi!


terrace=/aario/is/a/considerate/boy.friend.thigh
#       #   : remove left, the 1st from left
#       ##  : remove left, the last from left
#       %   : remove right, the 1st from right
#       %%  : remove right, the last from right
echo ${terrace##*/}         # boy.friend.thigh
echo ${terrace##*.}         # thigh
echo ${terrace#*.}          # friend.thigh
echo ${terrace%/*}          # /aario/is/a/considerate
echo ${terrace%%.*}         # /aario/is/a/considerate/boy


echo ${scores[0]}
echo ${scores[*])}   # 
echo ${scores[@])}   # 

for i in ${scores[@]}; do
done

echo ${#scores[*]}   # sizeof(scores)
echo ${#scores[0]}   # strlen(scores[0])

echo ${#DATE}  # strlen($DATE)
echo ${DATE:0:3}   # substr($DATE)
echo ${1: -2}       # substr($1, -2)


echo ${DATE_UPTIME:?"error msg"}    # if [ ! -z DATE_UPTIME ]; error 
echo ${DATE:+"2015-05-05"}           # [ ! -z $DATE ] ? "2015-05-05" && $DATE
echo ${DATE:-"2015-05-05"}   # exists $DATE && $DATE != "" : $DATE ? "2015-05-05"
echo ${USER:=1}             #  USER = exists $DATE && $DATE != "" ? $USER : 1, return $USER

echo ${NAME:="Aario"}       # DO NOT USE IT to indicate NAME = NAME : NAME ? "Aario"
                            # It'll echo the words, and there's an `echo` keyword
NAME=${NAME:-"Aario"}       # Suggest!!!

echo "$appellation"

# Lower-case, with underscores to separate words. Separate libraries with ::. 
# Parentheses are required after the function name. The keyword function is 
# optional, but must be used consistently throughout a project.
# 
fn() {
  local extraneous  # Declare function-specific variables with local. 
  extraneous="$1" || return   # Declaration and assignment should be on different lines.
  
  echo "$@"
  for i in $@; do
    echo "i=$i"
  done
  echo "args[0] = $1"
  echo "args = $[*]"
  return 100;
}

fn Saga Legend
|[
    $@ =  Saga Legend
]|




unset .f fn         # .f is necessary

# STDIN_FILENO(0)  STDOUT_FILENO(1)  STDERR_FILENO(2)
command < $file    # stdin reads from $file instead of keyboard
command 2 > $file   # save stderr to $file instead of printing on screen
command 1 >> $file  # append stdout to $file
command > $file 2>&1 #  combine stderr stdout to $file
command >> $file 2>&1
command < $file_in > $file_out  # save stdin to $file_in; stdout to $file_out
command > /dev/null # normally use for daemon process - run without stdout
command > /dev/null 2>&1

# -o(or) -a(and) !(not)
# -eq $num -ne $num -gt -lt -ge(great and equal) -le
# == $string != $string
# -z $str (isempty($str))  
# -s $file   is file not empty
# -b $file  is $file a device file
# -c $file  is $file a character device file
# -d $dir   is $dir a directory
# -f $file  is a normal file (either a device nor a character file)
# -g $file  is setting SGID bit
# -k $file  is setting Stricky bit
# -p $file  is a pipe
# -u $file  is setting SUDI bit
# -r $file  is readble
# -w $file  is writable
# -x $file  is executable
# -s $file  is filesize($file) != 0
# -e $path  is $path exist

# Put `; do` and `; then` on the same line as the while, for or if.


######################################################
# -a -o needs quoted by []

lament=1
[ $lament -eq 1 ] || echo "lament"     # not echo
[ $lament -eq 1 ] && echo "lament"

if [ -z $appellation -a $CONST_NUM -ne 0 ]; then 
# && || needs quoted by [[]]
if [ -z $appellation ] && [ $CONST_NUM -ne 0 ]; then 
if [[ -z $appellation && $CONST_NUM -ne 0 ]]; then 
######################################################
  s=`expr $CONST_NUM + 4`     #1004
  c=`expr $CONST_NUM \* 2`
elif []
then
else []
fi

# [[ ... ]] is preferred over [, test and /usr/bin/[. 
# [[ ... ]] reduces errors as no pathname expansion or word splitting takes 
#   place between [[ and ]] and [[ ... ]] allows for regular expression matching 
#   where [ ... ] does not.

# [[:alnum:]] = [[:alpha:]] + number
if [[ "semen" =~ ^[[:alnum:]]+men ]]; then
  echo "Match"
fi


for skill in 1 2 3 4 5; do      # for $str in "Hello, Aaron!"
  echo $$       # pid of current process
  echo $0       # pwd
  echo $*       # all arguments in one string, e.g. "arg1 arg2 ..."
  echo $@       # all arguments seperated, e.g. "arg1" "arg2" ...
  echo $n       # *(argv+n)
  echo $#       # int argc
  echo ${!#}   # last arg
  echo $?       # exit status, 0 on success; 1 on error
done

set -- arg1 arg2   # set arguments
echo $#   # 2
echo $@   # arg1 arg2


#semen.txt
#   One
#   One
#   Semen
#   And
#   And
#   One
#   One
#   Ovum
#


i=0;
for((i=1;i<100;++i)); do
  echo $i;
done
echo $i         # now i=100

# @note Use process substitution or for loops in preference to piping to while. 
#   Variables modified in a while loop do not propagate to the parent because the 
#   loop's commands run in a subshell.
#   The implicit subshell in a pipe to while can make it difficult to track down bugs.

line='__init'
senary='__init'
cat semen.txt | uniq | while read line; do
  line="last line: ${line}"     # it's subshell process, not the parent process
  senary=$line
done
echo $line;     # __init
echo $senary    # __init

line='init'
for line in $(cat semen.txt | uniq); do
  line="Last Line: ${line}";    # it's in the parent process
done
echo $line;     # Last Line: Ovum


for i in 1 2 3; do
    for j in 4 5 6; do
        if [ $i -eq 2 ]; then
            continue                # continue all, i and j
            continue 1              # continue j
        fi
        if [ $j -eq 5 ]; then
            break 1                 # break for j...
        fi
        if [ $i -eq 3 ]; then
            break 2                 # break j and i       
            break                   # break all, j and i
        fi
    done
done

# Using process substitution allows redirecting output but puts the commands 
#   in an explicit subshell rather than the implicit subshell that bash creates 
#   for the while loop.
line='__init'
senary='__init'
while read line; do
  line="last line: ${line}";
  senary=$line
done < <(cat semen.txt | uniq)
echo $line    # EMPTY
echo $senary  # last line: Ovum

# Use while loops where it is not necessary to pass complex results to the parent 
#   shell - this is typically where some more complex "parsing" is required. 
#   Beware that simple examples are probably more easily done with a tool such 
#   as awk. This may also be useful where you specifically don't want to change 
#   the parent scope variables.

# Trivial implementation of awk expression:
#   awk '$3 == "nfs" { print $2 " maps to " $1 }' /proc/mounts
cat /proc/mounts | while read src dest type opts rest; do
  if [[ ${type} == "nfs" ]]; then
    echo "NFS ${dest} maps to ${src}"
  fi
done  



case ${file:0:2} in
  cn) echo "China" ;;
  en) echo "USA" ;;
  *) echo "default" ;;
esac

select opt in $@; do
    case $opt in
      Aario | 艾睿 | AarioAi )
        echo "First Name: Aario"
        ;;
      Ai)
        echo "Last Name: Ai"
        ;;
    esac
done

# a:     ==> sh$ -a 100              value is required
# bcd    ==> sh$ -b -c -d            value is not allowed
# 
while getopts 'a:bcedf' opt   
do
    case $opt in
        a)
            echo "$OPTARG"
        ;;
        b)
            echo "$OPTARG"
        ;;
        \?)
            echo "$OPTARG"
        ;;
    esac
done

# sh$ a.sh -op


f() {
    local i=0;
    local args=""
    local a_arg
    local last_arg
    for arg in $@; do
        if [ ! -z "$last_arg" ]; then 
            case $last_arg in
                -a)
                    a_arg=$arg
                ;;
            esac
            unset last_arg
            continue;
        fi
        case $arg in
            -a)
                echo "LOVE"
                last_arg='-a'
            ;;
            *)
                echo "$$($i)"
            ;;
        esac
        echo "$i: $arg"
        i=$[ $i + 1 ]
    done
    echo "::: $a_arg"
}

f -a 100  200


# check whether a command ,e.g. curl, success or not
if curl "http://127.0.0.1"; then
    echo "Curl Success"
fi

curl "http://127.0.0.1"
if [ $? -eq 0 ]; then
    echo "Sucess"
fi



# ping network connection
if ping 127.0.0.1 -c 1; then
    echo "Success"
fi


