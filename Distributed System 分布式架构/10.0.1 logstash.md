* https://www.elastic.co/guide/en/logstash/current/first-event.html

```
sh$ bin/logstash -e 'input { stdin { } } output { stdout {} }'
```
The -e flag enables you to specify a configuration directly from the command line. Specifying configurations at the command line lets you quickly test configurations without having to edit a file between iterations. This pipeline takes input from the standard input, stdin, and moves that input to the standard output, stdout, in a structured format.

Once "Pipeline main started" is displayed, type hello world at the command prompt to see Logstash respond:
```
hello world                                                         <--  STDIN
2013-11-21T01:22:14.405+0000 0.0.0.0 hello world                    <-- logstash response
```

Use the -f <path/to/file> option to specify the configuration file that defines that instance¡¯s pipeline.

A Logstash pipeline has two required elements, input and output, and one optional element, filter. 

```xxx.conf
# The # character at the beginning of a line indicates a comment. Use
# comments to describe your configuration.
input {
}
# The filter part of this file is commented out to indicate that it is
# optional.
# filter {
#
# }
output {
}


```
# 
## input
*   file: reads from a file on the filesystem, much like the UNIX command tail -0F
*   syslog: listens on the well-known port 514 for syslog messages and parses according to the RFC3164 format
*   redis: reads from a redis server, using both redis channels and redis lists. Redis is often used as a "broker" in a centralized Logstash installation, which queues Logstash events from remote Logstash "shippers".
*   beats: processes events sent by Filebeat.

## filter
https://www.elastic.co/guide/en/logstash/current/filter-plugins.html

*   grok: parse and structure arbitrary text. Grok is currently the best way in Logstash to parse unstructured log data into something structured and queryable. With 120 patterns built-in to Logstash, it¡¯s more than likely you¡¯ll find one that meets your needs!
*   mutate: perform general transformations on event fields. You can rename, remove, replace, and modify fields in your events.
*   drop: drop an event completely, for example, debug events.
*   clone: make a copy of an event, possibly adding or removing fields.
*   geoip: add information about geographical location of IP addresses (also displays amazing charts in Kibana!)

## outputs
*   elasticsearch: send event data to Elasticsearch. If you¡¯re planning to save your data in an efficient, convenient, and easily queryable format¡­ Elasticsearch is the way to go. Period. Yes, we¡¯re biased :)
*   file: write event data to a file on disk.
*   graphite: send event data to graphite, a popular open source tool for storing and graphing metrics. http://graphite.readthedocs.io/en/latest/
*   statsd: send event data to statsd, a service that "listens for statistics, like counters and timers, sent over UDP and sends aggregates to one or more pluggable backend services". If you¡¯re already using statsd, this could be useful for you!

## codecs
https://www.elastic.co/guide/en/logstash/current/codec-plugins.html

* json
* multiline



```
sh$ bin/logstash -f xxx.conf
```


```tutorial.conf
input {
    file {
        path => "/var/log/nginx/access.log"
        path => "/var/log/nginx/*.log"
        start_position => beginning 
        ignore_older => 0 
    }
    
    /**
     * Start a TCP Server with port 12345 to receive log data
     */
    tcp {   
        port => 12345
        port => "${LOSTASH_TCP_PORT}"
        port => "${LOSTASH_TCP_PORT:54321}"
    }
}



// https://github.com/elastic/logstash/blob/v1.1.9/patterns/grok-patterns

filter {
    grok {
        /**
         * (?:%{USER:ident}|-)     ==>  ? : 
         */
        match => ["message", "%{IPORHOST:client} (%{USER:ident}|-) (%{USER:auth}|-) \[%{HTTPDATE:timestamp}\] \"(?:%{WORD:verb} %{NOTSPACE:request}(?: HTTP/%{NUMBER:http_version})?|-)\" %{NUMBER:response} %{NUMBER:bytes} \"(%{QS:referrer}|-)\" \"(%{QS:agent}|-)\""]
    }
    date {
            match => [ "timestamp" , "dd/MMM/yyyy:HH:mm:ss Z" ]
    }
    
    if [path] =~ "access" {
        mutate { replace => { "type" => "nginx_access" } }
        date {
            match => [ "timestamp" , "dd/MMM/yyyy:HH:mm:ss Z" ]
        }
    } else if [path] =~ "error" {
        mutate { replace => { "type" => "nginx_error" } }
    } else {
        mutate { replace => { "type" => "nginx_unknown" } }
    }
    
    
    mutate {
        /**
         *  return {
         *      "message" : "",
         *      "@version": "1",
         *      ...
         *      "tags" : ["aa_tag1", ""]
         *  }
         */
        add_tag => [ "aa_tag1", "${ENV_TAG}" ]
        
        /**
         *  return {
         *      "message" : "",
         *      "@version" : "1",
         *      ...
         *      "aa_path" : "/tmp/aa.log"
         *  }
         */
        add_field => {
            "aa_path" => "/tmp/aa.log"
        }
    }
}

output {
    kafka { 
        topic_id => 'logstash_logs' 
    }
    elasticsearch {
        hosts => ["IP Address 1:port1", "IP Address 2:port2", "IP Address 3"]
    }
    stdout {
        codec => multiline
    }
    file {
        codec => json
        path => "/var/log/logstash/logstash.log"
        path => "/var/log/%{type}.%{+yyyy.MM.dd.HH}"
    }
}
```



	
The default behavior of the file input plugin is to monitor a file for new information, in a manner similar to the UNIX tail -f command. To change this default behavior and process the entire file, we need to specify the position where Logstash starts processing the file.

The default behavior of the file input plugin is to ignore files whose last modification is greater than 86400s. To change this default behavior and process the tutorial file (which date can be much older than a day), we need to specify to not ignore old files.

# Samples

```logstash.nginx
input {
    file {
        path => "/var/log/nginx/*.log"
        start_position => beginning
        ignore_older => 1
    }
}

filter {
    grok {
         match => ["message", "%{IPORHOST:client} (%{USER:ident}|-) (%{USER:auth}|-) \[%{HTTPDATE:timestamp}\] \"(?:%{WORD:verb} %{NOTSPACE:request}(?: HTTP/%{NUMBER:http_version})?|-)\" %{NUMBER:response} %{NUMBER:bytes} \"(%{QS:referrer}|-)\" \"(%{QS:agent}|-)\""]
    }
    date {
        match => [ "timestamp" , "dd/MMM/yyyy:HH:mm:ss Z" ]
    }
    if [path] =~ "access" {
        mutate { replace => { "type" => "nginx_access" } }
    } else if [path] =~ "error" {
        mutate { replace => { "type" => "nginx_error" } }
    } else if [path] =~ "entrypoint" {
        mutate { replace => { "type" => "nginx_entrypoint" } }
        date {
            match => [ "timestamp" , "MMM dd HH:mm:ss Z" ]
        }
    }
    
    urldecode {
        all_fields => true
    }
}

output {
    stdout {}
    file {
        codec => json
         path => "/var/log/logstash/%{type}"
    }
}
```
