package main

import (
	"log"
	"fmt"
	"github.com/streadway/amqp"
	"flag"
)

func err(e error, msg string) {
	if e != nil {
		log.Fatalln(msg, e)
		panic(fmt.Sprintf(msg, e))
	}
}
/**
go run 10.2.2 mq-fanout-pub.go
	fanout:   -x logs_fanout -kind fanout -v "It's Fanout"
	direct:   -x logs_direct -kind direct -k info -v "info logs"
			  -x logs_direct -kind direct -k error -v "error logs"

go run 10.2.2 mq-fanout-sub.go
	fanout:  -x logs_fanout -kind fanout [-q mq_fanout_q1]   // 每个 Channel 一个 queue name，默认系统随机
	direct:  -x logs_direct -kind direct -k info [-q mq_fanout_q1]		// 只接受 info 日志
			 -x logs_direct -kind direct -k error [-q mq_fanout_q1]		// 只接受 error 日志
 */
func main() {
	x := flag.String("x", "logs", "exchange")
	kn := flag.String("kind", "fanout", "kind")
	k := flag.String("k", "", "routing key")
	vt := flag.String("vt", "text/plain", "Content Type")
	v := flag.String("v", "Hello, Aario!", "value")
	flag.Parse()
	ex := *x
	kind := *kn
	content_type := *vt
	val := *v
	routing_key := *k

	conn, e := amqp.Dial("amqp://guest:guest@localhost:5672/")
	defer conn.Close()
	err(e, "Connection")
	ch, e := conn.Channel()
	defer ch.Close()
	err(e, "Channel()")
	e = ch.ExchangeDeclare(
		ex,
		kind,
		true,
		false,
		false,
		false,
		nil,
	)
	err(e, "ExchangeDeclare()")
	e = ch.Publish(
		ex,
		routing_key,					// fanout 时， key 无效
		false,
		false,
		amqp.Publishing{
			ContentType: content_type,
			Body: []byte(val),
		},
	)

	fmt.Println("Exchange: ", ex, "; Kind", kind, "; Key: ", routing_key, ";")
}
