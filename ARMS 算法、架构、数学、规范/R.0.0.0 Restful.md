# Error Code
```
/**
 * Error Code
 * Make an alias and require another one error code constant sheet if you need
 *  another one error code design.
 * According to the principle `human-oriental`, make it constant instead of struct.
 * @note start with E_ will somehow conflict with PHP http://php.net/manual/en/errorfunc.constants.php
 * @see https://developer.mozilla.org/en-US/docs/Web/HTTP/Response_codes
 * @see http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml
 * @see http://www.restapitutorial.com/httpstatuscodes.html
 */
E0_UNKNOWN = 0; // mostly it refers to E_OK 200,

E200_OK = 200;          /* GET success */
E201_CREATED = 201;     /* POST/PUT/PATCH success */
E202_ACCEPTED = 202;
E203_NON_AUTHORITATIVE_INFORMATION = 203;
E204_NO_CONTENT = 204;   /* DELETE success */
E205_RESET_CONTENT = 205;
E206_PARTIAL_CONTENT = 206;
E207_MULTI_STATUS = 207;

E300_MULTIPLE_CHOICES = 300; /* it's unlikely to change. cache it */
E301_MOVED_PERMANENTLY = 301;
E302_FOUND = 302;


|- 4xx Client Error  --> show to client -|


E400_BAD_REQEUST = 400;   /* POST/PUT/PATCH bad syntax or parameters */
E401_UNAUTHORIZED = 401;  /* need authority, username or password error */
E402_PAYMENT_REQUIRED = 402;
E403_FORBIDDEN = 403;     /* diffirent to 401, authorized but forbidden */
E404_NOT_FOUND = 404;
E405_METHOD_NOT_ALLOWED = 405;

/**
 * GET the request accept-type error, e.g. request xml, but only json avaliable
 */ 
E406_NOT_ACCEPTABLE = 406;
E407_PROXY_AUTHENTICATION_REQUIRED = 407;
E408_REQUEST_TIMEOUT = 408;
E409_CONFLICT = 409;
/**
 * GET this response would be sent when requested content has been deleted from server
 */
E410_GONE = 410;
E411_LENGTH_REQUIRED = 411;
E412_RECONDITION_FAILED = 412;
E413_REQUEST_ENTITY_TOO_LARGE = 413;
E414_REQUEST_URI_TOO_LONG = 414;
E415_UNSUPPORTED_MEDIA_TYPE = 415;
E416_REQUESTED_RANGE_NOT_SATISFIABLE = 416;
E417_EXPECTATION_FAILED = 417;

E421_TOO_MANY_REQUEST = 421;
E421_THERE_ARE_TOO_MANY_CONNECTIONS_FROM_YOUR_INTERNET_ADDRESS = 421;

E422_UNPROCESSABLE_ENTITY = 422;  /* POST/PUT/PATCH failed validation */
E423_LOCKED = 423;
E424_FAILED_DEPENDENCY = 424;
E425_UNORDERED_COLLECTION = 425;
E426_UPGRADE_REQUIRED = 426;

E431_REQUEST_HEADER_FIELDS_TOO_LARGE = 431;
E444_NO_RESPONSE = 444;             // nginx
E449_RETRY_WITH = 449;              // microsoft
E499_CLIENT_CLOSED_REQUEST = 499;   // nginx

|- 5xx Server Error --> write in to log -|

E500_SERVER = 500;            // alias to E_INTERNAL_SERVER_ERROR
E500_INTERNAL_SERVER_ERROR = 500;

E501_NOT_IMPLEMENTED = 501;
E502_BAD_GATEWAY = 502;
E503_SERVICE_UNAVAILABLE = 503;
E504_GATEWAY_TIMEOUT = 504;
E505_HTTP_VERSION_NOT_SUPPORTED = 505;

E598_NETWORK_READ_TIMEOUT = 598;
E599_EXTERNAL_SERVER = 599;

E600_UNPARSEABLE_RESPONSE_HEADERS = 600;
```
# Suggestion
###  version
```
/v1/
```
### response
```json
/**
 * @see https://en.wikipedia.org/wiki/HATEOAS
 * @see http://svn.apache.org/viewvc/httpd/httpd/trunk/docs/conf/mime.types?view=markup
 */
{
  "link": {
    "rel": "collection http://www.luexu.com/users", /* relation , collection = list */
    "href": "",                                     /* the next url */
    "title": "the title of this API",
    "type": "",                                     /* API content type */
  },
  "errmsg": "error message",
  "errcode": 200,
  "res": [] | {}            /* response */
}
```

# Theory
```
/**
 * GET / POST / HEAD / PUT(insert) / PATCH(update) / DELETE / TRACE / CONNECT / OPTIONS
 */
```
## Restful
```
Consumer(Client)   ------------->    Service(Server) 
Stateless
  There is no consumer state session in service. Consumers should send its 
  session status to service.
Cache
  The service should be stateless and without cache
  +----------+                                  +------------------------+
  | Consumer | -------------------------------> |         Service        |
  |  cache   | --->[Intermediary with cache]--> | stateless and no cache |
  +----------+                                  +------------------------+
Interface / Uniform Contract
  URL  ------   HTTP Methods -------- media type (e.g. Content-type:json)
```
#  Header
```
Accept
Content-type  application/json



href  URI
rel   relationship
    http://www.w3.org/TR/2012/WD-html5-20121025/links.html#linkTypes
    self        指向当前资源本身的链接的 rel 属性。每个资源的表达中都应该包含此关系的链接。
    edit        指向一个可以编辑当前资源的链接。
    item        如果当前资源表示的是一个集合，则用来指向该集合中的单个资源。
    collection   如果当前资源包含在某个集合中，则用来指向包含该资源的集合。
    alternate   相同资源的另一版本的链接
    edit        可以编辑资源的URI
    related     相关资源
    previous
    next
    first
    last
    search      指向一个可以搜索当前资源及其相关资源的链接。
title   
type  optional, mime type
hreflang  optional, 
length  optional,

/rels/detail
/rels/author
/rels/book


HTTP/1.1 201 Created
Location: http://www.luexu.com/hires/099
{
    "name": "Aario",
    "id": "urn:dev:hr:hiring:099",
    "link":{
        "rel": "http://www.luexu.com/rels/hiring/post-ref-result",
        "href": "http://www.example.com/hires/099/refs",
    }
}  
```
# URI templates
```
http://www.luexu.com/segment1/{token}/segement2?param1={p1}&param2={p2}
http://www.luexu.com/segment1/{token}/segement2;longitude={p1};latitude={p2}

|[
  "link-templates": [
    {
      "rel": "http://www.luexu.com/rels/detail",
      "href": "http://www.example.com/customers/{customer-id}",
      "title": "View Customer Detail"
    }, {
      "rel": "http://www.luexu.com/rels/search",
      "href": "http://www.example.com/search/k={keyword}&p={page-number}&r={results-per-page}",
      "title": "Search Results"
    }
  ]

]|
```