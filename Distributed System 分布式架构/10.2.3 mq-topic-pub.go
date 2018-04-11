package main

import (
	"github.com/streadway/amqp"
	"flag"
	"fmt"
)

func main() {
	x := flag.String("x", "logs_topic", "exchange")
	k := flag.String("k", "hello", "routing key")
	vt := flag.String("vt", "text/plain", "Content Type")
	v := flag.String("v", "Hello, Aario!", "value")
	flag.Parse()
	ex := *x
	content_type := *vt
	val := *v
	routing_key := *k

	conn, _ := amqp.Dial("amqp://guest:guest@localhost:5672/")
	defer conn.Close()
	ch, _ := conn.Channel()
	defer ch.Close()
	ch.ExchangeDeclare(
		ex,
		"topic",
		true,
		false,
		false,
		false,
		nil,
	)
	ch.Publish(
		ex,
		routing_key,
		false,
		false,
		amqp.Publishing{
			ContentType: content_type,
			Body: []byte(val),
		},
	)

	fmt.Println("Exchange: ", ex, "; Key: ", routing_key, ";")
}
