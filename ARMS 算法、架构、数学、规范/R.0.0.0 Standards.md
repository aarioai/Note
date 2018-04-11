# Terms

[MUST / MUST NOT / SHOULD / SHOULD NOT](http://tools.ietf.org/html/rfc2119)

[MUST/REQUIRED/SHALL MUST NOT/ SHALL NOT SHOULD/RECOMMENDED SHOULD NOT/NOT RECOMMENDED](http://tools.ietf.org/html/rfc4949)


## Date Format
[HTTP Date](http://search.cpan.org/~gaas/HTTP-Date-6.02/lib/HTTP/Date.pm)
[HTTP Date/Time](https://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html)
### HTTP Datetime
> All HTTP date/time stamps MUST be represented in Greenwich Mean Time (GMT), without exception. For the purposes of HTTP, GMT is exactly equal to UTC (Coordinated Universal Time). This is indicated in the first two formats by the inclusion of "GMT" as the three-letter abbreviation for time zone, and MUST be assumed when reading the asctime format. HTTP-date is case sensitive and MUST NOT include additional LWS beyond that specifically included as SP in the grammar.
```
"Wed, 09 Feb 1994 22:23:32 GMT"       -- HTTP format
"Thu Feb  3 17:03:55 GMT 1994"        -- ctime(3) format
"Thu Feb  3 00:00:00 1994",           -- ANSI C asctime() format
"Tuesday, 08-Feb-94 14:15:29 GMT"     -- old rfc850 HTTP format
"Tuesday, 08-Feb-1994 14:15:29 GMT"   -- broken rfc850 HTTP format

"03/Feb/1994:17:03:55 -0700"   -- common logfile format
"09 Feb 1994 22:23:32 GMT"     -- HTTP format (no weekday)
"08-Feb-94 14:15:29 GMT"       -- rfc850 format (no weekday)
"08-Feb-1994 14:15:29 GMT"     -- broken rfc850 format (no weekday)

"1994-02-03 14:15:29 -0100"    -- ISO 8601 format
"1994-02-03 14:15:29"          -- zone is optional
"1994-02-03"                   -- only date
"1994-02-03T14:15:29"          -- Use T as separator
"19940203T141529Z"             -- ISO 8601 compact format
"19940203"                     -- only date

"08-Feb-94"         -- old rfc850 HTTP format    (no weekday, no time)
"08-Feb-1994"       -- broken rfc850 HTTP format (no weekday, no time)
"09 Feb 1994"       -- proposed new HTTP format  (no weekday, no time)
"03/Feb/1994"       -- common logfile format     (no time, no offset)

"Feb  3  1994"      -- Unix 'ls -l' format
"Feb  3 17:03"      -- Unix 'ls -l' format

"11-15-96  03:52PM" -- Windows 'dir' format
```

/**
 *  S = SQL
 *  A = API
 */
A     timeline       /* dynamic information list, e.g. message/timeline */
A     batch          /* multiple. e.g. comments/show_batch */
A     count          /* the number, e.g. comments/count */
AS    archive        /* for backup, e.g. MySQL table: order_archive */
AS    log            /* for logging, e.g. MySQL table: user_registry_log */


# Abbreviation
[fn] function : accepted in keyboard

|+ Doc maker +|
/**
 * @var   --> @field  @constant  @define
 * @param       --> @arg
 * @param  --> value-result
 * @return  --> @returns
 * @throw  
 * @todo
 * @see   --> @link @tutorial
 * @author
 * @version
 * @example
 * @extends --> @derive
 * @note  -->  @note   @remind @note     
 * int array bool string
 
 *******************************
 * @alias Treat a member as if it had a different name.
 * 
 */
|[

char leadPoisoning(int &value_result){
}

int fart = 5;               // @var
#define profound 100        // @var  --> @define
const int markdown = 10;    // @var  --> @constant

enum fuzzy{
  PERHAPS,    // @var   --> @constant
};
union recipe{
  size_t cuisine;         // @var  --> @field
};

]|

|! Must/Required/Shall !|
|+ Standard Operator Precedence[ˈprɛsɪdəns] +|
/**
 * @see http://php.net/manual/en/language.operators.precedence.php
 * @see http://en.cppreference.com/w/cpp/language/operator_precedence
 * @see http://en.cppreference.com/w/c/language/operator_precedence
 */

+------------------------------------------------------------------------------+
|L| X++ X-- type()  Cls.prop ClsPtr->prop  
+------------------------------------------------------------------------------+
|R| !(logic NOT) ~(bitwise NOT)
|R| *(ptr)  &(address-of)
+------------------------------------------------------------------------------+
|R| * / %
|R| +(Addition) -(substraction)
|R| << >>
|L| <  >  <=  >=
| | ==  !==   ===  !==
|L| &(bitwise AND)
|L| ^
|L| |
|L| &&  AND(MySQL)
|L| ||  OR(MySQL)
| | ?:
|R| = 
|R| +=  -= 
|R| *=  /=  .=  %= 
|R| <<=  >>= 
|R| &= |= ^=
|L| ,
+------------------------------------------------------------------------------+ 

|! Should/Recommended !|
|+ How to put braces +|
```
/**
 *  Upper-camel and next line brace
 *    namespace and class
 *  Lower-camel and brace behind
 *    non-construct/non-destruct functions
 *  Snake
 *    local variables
 * Only braces of namespace and class turn to the next line
 */
```
```
void allFunctionMayBeTrunedToPublic() {

}
namespace Bowtie {
  class Sewer: public Drain, public Drainage {
    int sewage;
    public:
    Sewer();
    void sewerage(int exit_val) {
      if(EXIT_SUCCESS == exit_val) {
        printf("Success");
      } else if(EXIT_FAILUE == exit_val) {
        printf("Failue");
      }
    }
  }
}
```
#### Don't use ++ += -- -= 
```
    ++ += -- -= is not allowed in Swift and lua
```
#### Use soft tab(4 spaces) to replace hard tab



Pros
* "Indent 2 spaces, no tabs" is a rule in google shell guider

Cons
* Swift official suggestion
* It's default setting for most IDEs!
* Facebook sets it 1 space; Google sets it 2 spaces;
* It's good for comments
* It's really good for HTML coding
* 4 spaces is not good for shell and doc commentary. 1 is so short;
* Use tab to indent, use space to align.
* If you are using space, you are making align, not making indent.
```

#### Don't Prepend an underline to private variables
|- Pros -|
  It's quite not good for writing code when you have no design.
|- Cons -|
  It's python standard
  It's accepted in PHP/C++/C that name a variable begin with an underline
  Facebook names a private variable to append an underline
https://github.com/facebook/proxygen/blob/master/proxygen/httpserver/HTTPServer.cpp





|+ Right value should be put at left when compare it +|
if(true == isAready)     // 
if(true = isAready) //  compiler will indicate error

if(isAready == true) // 
if(isAready = true) // it's a mistake, but not easy to find



|+ Declaration Order: variables, methods; private, protected, public +|
Use the specified order of declarations within a class: private protected public; data  members (variables) before methods.
|- Pros -|
It's accepted in Facebook and it's more human readable.
|- Cons -|
It's contrary to Google C++ Guider "Declaration Order".

|+ Using i++ instead of ++i +|
|- Pros -|
`++i` is not supported in Go-lang
