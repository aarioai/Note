package main
import (
	"fmt"
	"github.com/streadway/amqp"
	"log"
	"flag"
)

func err(e error, msg string) {
	if e != nil {
		log.Fatalln(msg, e)
		panic(fmt.Sprintf(msg, e))
	}
}

func main() {
	q := flag.String("q", "test", "")
	v := flag.String("v", "Hello, Aario!", "")
	flag.Parse()
	queue := *q
	value := *v
	conn, e := amqp.Dial("amqp://Aa:Aa@localhost:5672/")
	defer conn.Close()
	err(e, "amqp.Dial()")
	ch, e := conn.Channel()
	defer ch.Close()
	err(e, "conn.Channel()")

	qd, e := ch.QueueDeclare(
		queue, 			// name
		false,   // durable
		false,	// delete when unused
		false,	// exclusive
		false,   // no-wait
		nil,   		// arguments
	)
	err(e, "Failed to declare a queue")

	e = ch.Publish(
		"",qd.Name, false, false, amqp.Publishing {
			ContentType:"text/plain", Body: []byte(value),
		})
	err(e, "channel.Publish()")
	fmt.Println("Published")
}