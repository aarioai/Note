```
https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml
https://support.microsoft.com/en-us/help/943891/the-http-status-code-in-iis-7-0--iis-7-5--and-iis-8-0
下面 分数部分都是仅 IIS 支持的

```
# 4xx Client Error The request contains bad syntax or cannot be fulfilled
```
400 Bad Request
	400.1 Invalid Destination Header.
  400.2 Invalid Depth Header.
  400.3 Invalid If Header.
  400.4 Invalid Overwrite Header.
  400.5 Invalid Translate Header.
  400.6 Invalid Request Body.
  400.7 Invalid Content Length.
  400.8 Invalid Timeout.
  400.9 Invalid Lock Token.
	400.10	Invalid XFF header
	400.11	Invalid WebSocket request
	400.601	Bad client request (ARR)
	400.602	Invalid time format (ARR)
	400.603	Parse range error (ARR)
	400.604	Client gone (ARR)
	400.605	Maximum number of forwards (ARR)
	400.606	Asynchronous competition error (ARR)
401  Unauthorized (HTTP/1.1) / Access Denied (IIS)
	- the request has not been applied because it lacks valid authentication credentials for the target resource. The origin server MUST send a WWW-Authenticate header field containing at least one challenge applicable to the target resource.
	 
	- WWW-Authenticate: Basic realm="My Realm"
			realm : A string to be displayed to users so they know which username and
     	password to use. This string should contain at least the name of
     	the host performing the authentication and might additionally
     	indicate the collection of users who might have access. An example
     	might be "aarioai@gmail.com".
     	- The realm attribute (case-insensitive) is required for all authentication schemes which issue a challenge. The realm value (case-sensitive), in combination with the canonical root URL of the server being accessed, defines the protection space. These realms allow the protected resources on a server to be partitioned into a set of protection spaces, each with its own authentication scheme and/or authorization database. The realm value is a string, generally assigned by the origin server, which may have additional semantics specific to the authentication scheme.
     - In short, pages in the same realm should share credentials. If your credentials work for a page with the realm "My Realm", it should be assumed that the same username and password combination should work for another page with the same realm.
	- 未登陆、登陆失败的，一律返回 401，并带 WWW-Authenticate realm="${scope}"
	
	401.1 登录失败 
	401.2 服务器配置问题导致登录失败 
	401.3 ACL 禁止访问资源 
	401.4 未授权：授权被筛选器拒绝 
	401.5 未授权：ISAPI 或 CGI 授权失败 

403 Forbidden 禁止访问，对 Internet 服务管理器 的访问仅限于 Localhost 
	- If authentication credentials were provided in the request, the server considers them insufficient to grant access. The client SHOULD NOT automatically repeat the request with the same credentials. The client MAY repeat the request with new or different credentials. However, a request might be forbidden for reasons unrelated to the credentials.
	- An origin server that wishes to "hide" the current existence of a forbidden target resource MAY instead respond with a status code of 404 (Not Found).
	- 已登陆的用户，如果权限问题，建议一律采用 403 （涉密的，用 404）。
	
	403.1  禁止访问：禁止可执行访问 
	403.2  禁止访问：禁止读访问 
	403.3  禁止访问：禁止写访问 
	403.4  禁止访问：要求 SSL 
	403.5  禁止访问：要求 SSL 128 
	403.6  禁止访问：IP 地址被拒绝 
	403.7  禁止访问：要求客户证书 
	403.8  禁止访问：禁止站点访问 
	403.9  禁止访问：连接的用户过多 
	403.10 禁止访问：配置无效 
	403.11 禁止访问：密码更改 
	403.12 禁止访问：映射器拒绝访问 
	403.13 禁止访问：客户证书已被吊销 
	403.15 禁止访问：客户访问许可过多 
	403.16 禁止访问：客户证书不可信或者无效 
	403.17 禁止访问：客户证书已经到期或者尚未生效
	403.18 Cannot execute requested URL in the current application pool.
  403.19 Cannot execute CGI applications for the client in this application pool.
  403.20 Forbidden: Passport logon failed.
  403.21 Forbidden: Source access denied.
  403.22 Forbidden: Infinite depth is denied.
  403.502 Forbidden: Too many requests from the same client IP; Dynamic IP Restriction limit reached.

404 Not Found
	404.1 Site Not Found.
	404.2 ISAPI or CGI restriction.
	404.3 MIME type restriction.
	404.4 No handler configured.
	404.5 Denied by request filtering configuration.
	404.6 Verb denied.
	404.7 File extension denied.
	404.8 Hidden namespace.
	404.9 File attribute hidden.
	404.10 Request header too long.
	404.11 Request contains double escape sequence.
	404.12 Request contains high-bit characters.
	404.13 Content length too large.
	404.14 Request URL too long.
	404.15 Query string too long.
	404.16 DAV request sent to the static file handler.
	404.17 Dynamic content mapped to the static file handler via a wildcard MIME mapping.
	404.18 Querystring sequence denied.
	404.19 Denied by filtering rule.
	404.20 Too Many URL Segments

405 Method Not Allowed 资源被禁止 

406 Not Acceptable 无法接受MIME类型
407 Proxy Authentication Required
408 Request Timeout
409 Conflict
410 Gone
411 Length Required
412 Precondition Failed
413 Payload Too Large
414 Request-URI Too Long
415 Unsupported Media Type
416 Requested Range Not Satisfiable
417 Expectation Failed
418 I'm a teapot
421 Misdirected Request
422 Unprocessable Entity
423 Locked
424 Failed Dependency
426 Upgrade Required
428 Precondition Required
429 Too Many Requests
431 Request Header Fields Too Large
444 Connection Closed Without Response
451 Unavailable For Legal Reasons
499 Client Closed Request
```
# 5xx Server Error The server failed to fulfill an apparently valid request
```
500 内部服务器错误 
	500.11 服务器关闭 
	500.12 应用程序重新启动 
	500.13 服务器太忙 
	500.14 应用程序无效 
	500.15 不允许请求 global.asa 
	500.19 Configuration data is invalid.
	500.21 Module not recognized.
	500.22 An ASP.NET httpModules configuration does not apply in Managed Pipeline mode.
	500.23 An ASP.NET httpHandlers configuration does not apply in Managed Pipeline mode.
	500.24 An ASP.NET impersonation configuration does not apply in Managed Pipeline mode.
	500.50 A rewrite error occurred during RQ_BEGIN_REQUEST notification handling. A configuration or inbound rule execution error occurred.
	Note Here is where the distributed rules configuration is read for both inbound and outbound rules.
	500.51 A rewrite error occurred during GL_PRE_BEGIN_REQUEST notification handling. A global configuration or global rule execution error occurred.
	Note Here is where the global rules configuration is read.
	500.52 A rewrite error occurred during RQ_SEND_RESPONSE notification handling. An outbound rule execution occurred.
	
	500.53 A rewrite error occurred during RQ_RELEASE_REQUEST_STATE notification handling. An outbound rule execution error occurred. The rule is configured to be executed before the output user cache gets updated.
	500.100 Internal ASP error.

501 Not Implemented  , Header values specify a configuration that is not implemented. 
502 Bad Gateway		 网关错误 
	502.1 CGI application timeout.
	502.2 Bad gateway: Premature Exit.  Map request failure (ARR)
	502.3 Bad Gateway: Forwarder Connection Error (ARR).  WinHTTP asynchronous completion failure (ARR)
	502.4 Bad Gateway: No Server (ARR).
  502.5	WebSocket failure (ARR)
  502.6	Forwarded request failure (ARR)
  502.7	Execute request failure (ARR)
503 Service Unavailable
	503.0 Application pool unavailable.
  503.2 Concurrent request limit exceeded.
  503.3 ASP.NET queue full
504 Gateway Timeout
505 HTTP Version Not Supported
506 Variant Also Negotiates
507 Insufficient Storage
508 Loop Detected
510 Not Extended
511 Network Authentication Required
599 Network Connect Timeout Error
```

# 3xx Redirection Further action must be taken in order to complete the request
```
300 Multiple Choices
301 Moved Permanently
302 Found
303 See Other
304 Not Modified
305 Use Proxy
307 Temporary Redirect
308 Permanent Redirect
```


# 2xx Success The action was successfully received, understood, and accepted
```
200 OK
201 Created
202 Accepted
203 Non-authoritative Information
204 No Content
205 Reset Content
206 Partial Content
207 Multi-Status
208 Already Reported
226 IM Used
```

# 1xx Informational Request received, continuing process
```
100 Continue
101 Switching Protocols
102 Processing
```