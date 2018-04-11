package main
import (
	"fmt"
	"github.com/streadway/amqp"
	"log"
	"flag"
)

func err(e error, msg string) {
	if e != nil {
		log.Fatalln(msg, err)
		panic(fmt.Sprintf(msg, err))
	}
}

func main() {
	q := flag.String("q", "test", "")
	flag.Parse()
	queue := *q
	conn, e := amqp.Dial("amqp://guest:guest@localhost:5672/")
	defer conn.Close()
	err(e, "amqp.Dial()")
	ch, e := conn.Channel()
	defer ch.Close()
	err(e, "conn.Channel()")
	/**
	 * consumer: unique string
	 * exclusive: When exclusive is true, the server will ensure that this is the sole consumer
from this queue. When exclusive is false, the server will fairly distribute
deliveries across multiple consumers.
	 * autoAck: a.k.a. noAck. On false, the consumer should call Delivery.Ack
	 */
	msgs, e := ch.Consume(queue, "", true, false, false, false, nil)
	err(e, "channel.Channel()")
	fmt.Println("Consumed ", queue)

	chan_block := make(chan bool)

	go func() {
		for d := range msgs {
			log.Printf("Received a message: %s", d.Body)
			fmt.Println("Received: ", d.Body)
		}
	}()
	<-chan_block
}