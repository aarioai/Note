package main

import (
	"github.com/streadway/amqp"
	"flag"
	"strconv"
	"fmt"
	"log"
)
func err(e error, msg string) {
	if e != nil {
		log.Fatalln(msg, err)
		panic(fmt.Sprintf(msg, err))
	}
}
func fib(n int) int {
	if n < 2{
		return n
	}

	return fib(n - 1) + fib(n - 2)
}
func main() {
	x := flag.String("x", "", "exchange")
	vt := flag.String("vt", "text/plain", "Content Type")

	q := flag.String("q", "rpc_queue_server", "queue")

	flag.Parse()
	ex := *x
	content_type := *vt
	queue := *q

	conn, _ := amqp.Dial("amqp://guest:guest@localhost:5672/")
	defer conn.Close()
	ch, _ := conn.Channel()
	defer ch.Close()
	qd, _ := ch.QueueDeclare(
		queue, false, false, false, false, nil,
	)

	// 设置每个queue最多同时持有多少条未ack的消息
	e := ch.Qos(1, 0, false)
	err(e, ".Qos()")

	msgs, e := ch.Consume(
		qd.Name, "", false, false, false, false, nil,
	)
	err(e, ".Consume()")

	sub_block := make(chan bool)
		go func() {
			for d := range msgs {
				n, _ := strconv.Atoi(string(d.Body))
				res := fib(n)
				ch.Publish(
					ex,
					d.ReplyTo,
					false,
					false,
					amqp.Publishing{
						ContentType:content_type,
						CorrelationId: d.CorrelationId,
						Body: []byte(strconv.Itoa(res)),
					},
				)
				d.Ack(false)
				fmt.Println("CI: ", d.CorrelationId, "; Re: ", d.ReplyTo)
			}
		}()

	<-sub_block
}