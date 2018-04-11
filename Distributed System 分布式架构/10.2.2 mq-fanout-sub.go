package main

import (
	"github.com/streadway/amqp"
	"log"
	"fmt"
	"flag"
)

func main() {
	x := flag.String("x", "logs", "exchange")
	kn := flag.String("kind", "fanout", "kind")
	k := flag.String("k", "", "routing key")
	q := flag.String("q", "", "queue")

	flag.Parse()
	ex := *x
	kind := *kn
	routing_key := *k
	queue := *q

	conn, _ := amqp.Dial("amqp://Aa:Aa@localhost:5672/")
	defer conn.Close()
	ch, _ := conn.Channel()
	defer ch.Close()
	ch.ExchangeDeclare(
		ex,
		kind,
		true,
		false,
		false,
		false,
		nil,
	)
	qd, _ := ch.QueueDeclare(
		queue,
		false,
		false,
		true,
		false,
		nil,
	)

	ch.QueueBind(
		qd.Name,
		routing_key,
		ex,
		false,
		nil,
	)

	// 设置每个queue最多同时持有多少条未ack的消息
	//ch.Qos(1, 0, false)

	msgs, _ := ch.Consume(
		qd.Name,
		"",
		true,
		false,
		false,
		false,
		nil,
	)

	fmt.Println("Exchange: ", ex, "; Kind", kind, "; Key: ", routing_key, ";")

	chan_block := make(chan bool)
	go func() {
		for d := range msgs {
			log.Printf("Received a message: %s", d.Body)
			fmt.Println("Received: ", d.Body)
		}
	}()
	<-chan_block
}
