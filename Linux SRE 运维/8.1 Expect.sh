#!/usr/bin/expect


# yum install -y expect
# Run expect in bash
```
#!/bin/bash
echo "Bash"
/usr/bin/expect <<-EOF
...
exepct eof
EOF
```

# variables 
set name "Aario"		# string variable
set say "Hello"
append say " "$name "!"    # set say "Hello Aario!"

length $name   # 5
tolower $name  # aario
toupper $name  # AARIO

compare "Aario" "Aa"
first $name "ri"      # strpos()
last $name "ri"       # rstrpos()
trim "!Aario!" "!"    # Aario
trimleft "!Aario!" "!" # Aario!
trimright "!Aario!" "!" # !Aario


set i 1
incr i     # i++   
set i [expr $i+3]    # i += 3





set arr(1) 100			# array variable
set arr(2) 200
set arr(100) Aario
array size arr			# 3


if { $i > 1 } {

}

switch $i {
0 {puts "i = 0";}
1 {puts "i = 1";}
}

for { set i 0 } { $i < 10 } { incr i } {puts $i}

while {$i<10} {
puts $i;
incr i;
}

foreach j {1 3 5} {
puts $j;
}


proc fn {i} {    # function
puts $i;
}

fn {1}	# call function


# Start a new process
spawn echo "LOVE"

if { [llength $argv] < 3} {
    puts "Usage:"				# echo
    puts "$argv0 port remote password  e.g. ./upload 22 root@88.88.88.88:/tmp"
    exit 1
}

set port [lindex $argv 0]
set remote [lindex $argv 1]
set passwd [lindex $argv 2]

set passwderror 0

spawn scp $base_dir/* $remote

expect {
    "*assword:*" {
        if { $passwderror == 1 } {
			puts "passwd is error"
			exit 2
        }
        set timeout 1000
        set passwderror 1
        send "$passwd\r"
        exp_continue
    }
    timeout {
        puts "connect is timeout"
        exit 3
    }
}
