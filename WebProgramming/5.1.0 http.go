// https://golang.org/pkg/net/http/#Handler

package main

import (
   	"io"
	"net/http"
	"log"
	//"time"
	"./go-lib/cookie"
	"./go-lib/cookietest"
	"runtime"
	"fmt"
    "github.com/NYTimes/gziphandler"
    "time"
)


/**
 *  is analogous to in Java
 *	class sayHello {
 *		public struct h
 *		public ServeHTTP(w, r) {}
 *	}
 */
type sayHello struct{}
func (h *sayHello) ServeHTTP(w http.ResponseWriter, r *http.Request) {





	w.Write([]byte("Hello, world!"))
	io.WriteString(w,"Helloooooooooo")
	log.Println("LOOOOOOOOOOOOOOOOOOG")
}

func goroutine(tag string) {
	for i := 0; i< 5; i++ {
		// 让出CPU给其他任务
		runtime.Gosched()
		fmt.Printf("%s%d\n", tag, i)
	}
}

func sayHelloFn(w http.ResponseWriter, r *http.Request) {
	go goroutine("new-")		// a new goroutine
	goroutine("cur-")			// current goroutine
	io.WriteString(w, "Testing Hello and goroutine...")
}


func postCookie(res http.ResponseWriter, req *http.Request) {
	ct := cookietest.Cookie{res, req}
	ct.Set("ct_type", "cookietest")
	ct.Set("ct_name", "Aario")

	c := cookie.New(res, req)
	c.Set("c_type", "cookie")
	c.Set("c_name", "Aario")

	io.WriteString(res, "cookie posted (注意：设置cookie必须在输出文字之前，否则之后的一律不会成功）\n")

}

func main() {
	mux := http.NewServeMux()

	/**
	    mux.Handle($route, $interface)  -> mux.Handle($route, &sayHello{})
	    mux.Handle($route, http.HandlerFunc(Handler))   -> mux.Handle($route, http.HandlerFunc(sayHello))
	    mux.HandleFunc($route, Handler)    --> mux.HandleFunc($route, sayHello)
	 */
	mux.Handle("/hello", &sayHello{})
	mux.HandleFunc("/post/cookie", postCookie)
	//mux.HandleFunc("/delete/cookie", deleteCookie)
	//mux.HandleFunc("/get/cookie", getCookie)
	mux.Handle("/", http.HandlerFunc(sayHelloFn))
	//http.ListenAndServe(":12345", http.FileServer(http.Dir(".")))


    // 添加 http gzip
    mux.Handle("/", gziphandler.GzipHandler(http.HandlerFunc(sayHelloFn)))

    serv := http.Server{
        Addr:  ":8888",
        Handler: mux,
        ReadTimeout: 5 * time.Second,
        WriteTimeout: 10 * time.Second,
    }
    fmt.Println(serv.ListenAndServe())
}