PASSWD_=""
OLD_DATA_DIR_="/var/lib/mysql"
NEW_DATA_DIR_=""
CONF_="/etc/my.cnf"

# shutdown mysql
mysqladmin -uroot -p$PASSWD_ shutdown

mv $OLD_DATA_DIR_ $NEW_DATA_DIR_"/"

# be careful about the blank near [ and ] and the semicolon
if [ ! -a "${CONF_}" ]; then
echo "NOT FOUND " $CONF_
exit
fi

# vim /etc/my.cnf , and modify  socket=$OLD_DATA_DIR_/mysql.sock to 
# socket=$NEW_DATA_DIR_/mysql.sock




# vim /etc/rc.d/init.d/mysql , and modify datadir=$OLD_DATA_DIR_ to 
# datadir=$NEW_DATA_DIR_=


/etc/rc.d/init.d/mysql start
