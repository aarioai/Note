# File
    dir/file  完整的路径
    path      部分路径
    name      不带路径分隔符
    
* work root:    <VARIABLE>
* work path:    <CONSTANT>
* work dir :    work root + work path
* dir:          path except filename , start with a slash, e.g. `/hello/Aario`
* dirname:      no slashes, e.g. `Aario`

* ext main name:  e.g. `jpg` `png` `gif`
* ext/extname:  e.g. `.jpg` `.png` `.gif`

* file main name:   filename without ext
* filename:     e.g. `hello.aario`
* file path:    <CONSTANT> some dirname(s) + filename
* file:         dir + filename
```
                dir
    ┌────────────┴───────────┐
       work dir
    ┌────────┴────────┐
   work root  work path dirname    extname
    ┌───┴──┐┌────┴────┐ ┌─┴─┐       ┌─┴─┐
    /var/lib/mysql/data/luexu/hello.aario
                              └────┬────┘ 
                             filename
    └───────────────────┬───────────────┘  
                      file

```

# URI
URL (Uniform Resource Locator, 必须要通过网络) ∈ URI (Uniform Resource ID，所有的资源ID)

https://en.wikipedia.org/wiki/Uniform_Resource_Identifier

* scheme:   当前页面使用的协议
* protocol: 获取客户端向服务器端传送数据所依据的协议名称
* host:  a registered name or IP address
* userinfo :  username[:password]
* authority:  [userinfo@]host[:port = 80]
* path:   must begin with a signle slash(/)
* hierarchical: authority[path]
```
scheme:[//authority][path][?query][#fragment]
scheme:[//[userinfo@]host[:port]][path][?query][#fragment]

//	URLs that do not start with a slash after the scheme are interpreted as:
//	e.g. mailto:pay@luexu.com, urn:hello:aario    常用在磁力下载
scheme:opaque[?query][#fragment]

```


```

                    hierarchical part
        ┌───────────────────┴───────────────────┐
                    authority             path
        ┌───────────────┴─────────────┐┌───┴────┐
  abc://username:password@luexu.com:123/path/data?key=value&key2=value2#fragid1
  └┬┘   └───────┬───────┘ └───┬───┘ └┬┘           └─────────┬─────────┘ └──┬──┘
scheme  user information     host     port                  query         fragment


                              opaque/path
         ┌───────────────────────────┴──────────────────────────┐
  magnet:?xt=urn:btih:LUEXU000AARIO000AI4C164EB2D8364463037ABD888      常用在磁力下载
  └──┬─┘
  scheme
         authority  path           query        fragment
          ┌───┴───┐┌─┴──┐ ┌──────────┴────────┐ ┌──┴──┐
  https://luexu.com/about?key=value&key2=value2#fragid1
  └─┬─┘   └───┬───┘     
  scheme    host(:port)           
```



```go
//	scheme://[userinfo@]host/path[?query][#fragment]
//	URLs that do not start with a slash after the scheme are interpreted as:
//	scheme:opaque[?query][#fragment]
type URL struct {
	Scheme     string
	Opaque     string    // encoded opaque data
	User       *Userinfo // username and password information
	Host       string    // host or host:port
	Path       string
	RawPath    string // encoded path hint (Go 1.5 and later only; see EscapedPath method)
	ForceQuery bool   // append a query ('?') even if RawQuery is empty
	RawQuery   string // encoded query values, without '?'
	Fragment   string // fragment for references, without '#'
}
```
#
```
lib
util
build   / dist  
  the distribution of building
  Build and dist both contain files created by the build process. But dist contains the ones that you actually want to keep at the end of it.
  Build directory is where files are compiled to. Dist directory is used for the distribution files (a place of the resulting package of the application).
builder
  e.g. node_modules
src
    the raw code, e.g. react jsx / uncompressed css
debug
test
```


