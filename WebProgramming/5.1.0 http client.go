package Go

/*
如果你向同一个HTTP服务器发送大量的请求，那么把保持网络连接的打开是没问题的。然而，如果你的应用在短时间内向大量不同的HTTP服务器发送一两个请求，那么在引用收到响应后立刻关闭网络连接是一个好主意。增加打开文件的限制数可能也是个好主意。
 */
func closeKeepAlive(url string) {
    req, err := http.NewRequest("GET", url, nil)
    if err !=nil {
        return
    }
    /*
     same as req.Header.Set("Connection", "close")
     这里优化 HTTP 连接，避免 keep alive
     如果你向同一个HTTP服务器发送大量的请求，那么把保持网络连接的打开是没问题的。然而，如果你的应用在短时间内向大量不同的HTTP服务器发送一两个请求，那么在引用收到响应后立刻关闭网络连接是一个好主意。增加打开文件的限制数可能也是个好主意。
      */
    req.Close = true

    resp, err := http.DefaultClient.Do(req)
    /*
    大多数情况下，当你的http响应失败时，resp变量将为nil，而err变量将是non-nil。然而，当你得到一个重定向的错误时，两个变量都将是non-nil。这意味着你最后依然会内存泄露。
    所以需要这样先判断
     */
    if resp != nil {
        defer resp.Body.Close()
    }
    if err != nil {
        return
    }

    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        return
    }
    fmt.Println(string(body))
}
func closeHTTP(url string) {
    /**
     http.Get() 其实就是 keepalive 的
     */
    resp, err := http.Get(url)
    // 一定要通过这个来关闭 Body
    if resp != nil {
        defer resp.Body.Close()
    }
    if err != nil {
        return
    }
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        return
    }
    fmt.Println(string(body))
}
