package main

import (
	"github.com/streadway/amqp"
	"flag"
	"strconv"
	"time"
	"math/rand"
	"fmt"
	"log"
)
func err(e error, msg string) {
	if e != nil {
		log.Fatalln(msg, err)
		panic(fmt.Sprintf(msg, err))
	}
}
func randString(l int) string {
	bytes := make([]byte, l)
	for i := 0; i < l; i++ {
		bytes[i] = byte(randInt(65, 90))
	}
	return string(bytes)
}

func randInt(min int, max int) int {
	return min + rand.Intn(max - min)
}

func main() {
	x := flag.String("x", "", "exchange")
	vt := flag.String("vt", "text/plain", "Content Type")
	k := flag.String("k", "rpc_queue_server", "routing key")
	v := flag.Int("v", 1, "value")
	q := flag.String("q", "", "queue")

	flag.Parse()
	ex := *x
	content_type := *vt
	routing_key := *k
	queue := *q
	n := *v

	conn, _ := amqp.Dial("amqp://guest:guest@localhost:5672/")
	defer conn.Close()
	ch, _ := conn.Channel()
	defer ch.Close()
	qd, _ := ch.QueueDeclare(
		queue, false, false, true, false, nil,
	)



	msgs, e := ch.Consume(
		qd.Name, "", true, false, false, false, nil,
	)
	err(e, ".Consume()")

	rand.Seed(time.Now().UTC().UnixNano())
	corr_id := randString(32)
	fmt.Println("CI: ", corr_id)

	ch.Publish(
		ex, routing_key, false, false, amqp.Publishing{
			ContentType:content_type,
			CorrelationId: corr_id,
			ReplyTo: qd.Name,
			Body: []byte(strconv.Itoa(n)),
		},
	)

	var res int
	for d := range msgs {
		if (corr_id == d.CorrelationId) {
			res, _  = strconv.Atoi(string(d.Body))
			break
		}
	}

	fmt.Println("Got: ", res)
}
