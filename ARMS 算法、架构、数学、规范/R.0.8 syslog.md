[Syslog](https://tools.ietf.org/html/rfc3164)
[Syslog](https://en.wikipedia.org/wiki/Syslog)
[PHP Syslog](http://php.net/manual/en/function.syslog.php)


## Syslog format
```
    <$pri>$header $msg
        $pri = $facility * 8 + $severity
        $header = timestamp + host or IP
        $msg = optional $process_name[optional $PID] $content
        e.g. <30>Oct 9 22:33:20 Aario auditd[1787]: The audit daemon is exiting.
            30 = `0001 1110` = `00011` + `110` = 3 * 8 + 6
                Facility = 3 system daemons
                Severity = 6 Informational
        e.g. <0>2016 June 08 10:52:01 TZ-6 scapegoat.dmz.example.org 10.1.2.3
         sched[0]: That's All Folks!
        e.g. <30>Oct 9 22:33:20 Aario : The audit daemon is exiting.
```
 If the originally formed message has a TIMESTAMP in the HEADER
         part, then it SHOULD be the local time of the device within its
         timezone.Implementers may wish to utilize the ISO 8601 [7] date and
   time formats if they want to include more explicit date and time
   information.
### Facility
The list of facilities available is defined by [RFC 3164](https://tools.ietf.org/html/rfc3164)
Note 1 - Various operating systems have been found to utilize
  Facilities 4, 10, 13 and 14 for security/authorization,
  audit, and alert messages which seem to be similar.
Note 2 - Various operating systems have been found to utilize
  both Facilities 9 and 15 for clock (cron/at) messages.
  
“kern”, “user”, “mail”, “daemon”, “auth”, “intern”, “lpr”, “news”, “uucp”, “clock”, “authpriv”, “ftp”, “ntp”, “audit”, “alert”, “cron”, “local0”..“local7”

```
0             kernel messages
1             user-level messages
2             mail system
3             system daemons
4             security/authorization messages (note 1)
5             messages generated internally by syslogd
6             line printer subsystem
7             network news subsystem
8             UUCP subsystem
9             clock daemon (note 2)
10             security/authorization messages (note 1)
11             FTP daemon
12             NTP subsystem
13             log audit (note 1)
14             log alert (note 1)
15             clock daemon (note 2)
16             local use 0  (local0)
17             local use 1  (local1)
18             local use 2  (local2)
19             local use 3  (local3)
20             local use 4  (local4)
21             local use 5  (local5)
22             local use 6  (local6)
23             local use 7  (local7)
```
### Severity
The Priority value is calculated by first multiplying the Facility
number by 8 and then adding the numerical value of the Severity. For
example, a kernel message (Facility=0) with a Severity of Emergency
(Severity=0) would have a Priority value of 0.  Also, a "local use 4"
message (Facility=20) with a Severity of Notice (Severity=5) would
have a Priority value of 165.  In the PRI part of a syslog message,
these values would be placed between the angle brackets as <0> and
<165> respectively.  The only time a value of "0" will follow the "<"
is for the Priority value of "0". Otherwise, leading "0"s MUST NOT be
used.
```
0	Emergency(emerg)    System is unusable	This level should not be used by applications.
1	Alert(alert)        Should be corrected immediately	Loss of the primary ISP connection.
2	Critical(crit)	    A failure in the system's primary application.
3	Error(err)	        An application has exceeded its file storage limit and attempts to write are failing.
4	Warning(warning)	May indicate that an error will occur if action is not taken. A non-root file system has only 2GB remaining.
5	Notice(notice)	    Events that are unusual, but not error conditions.	
6	Informational(info)	Normal operational messages that require no action.	An application has started, paused or ended successfully.
7	Debug(debug)	    Information useful to developers for debugging the application.	
```
### Mnemonic
### Message-text