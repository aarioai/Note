# The Base64 Alphabet
```
[A-Za-z0-9+/]   ==> 0 - 63   
(pad) =
```
# HTTP/2 Base 64 Encoding with URL and Filename Safe Alphabet
```
[A-Za-z0-9-_]      
(pad) =
```
An alternative alphabet has been suggested that would use "~" as the 63rd character.  Since the "~" character has special meaning in some file system environments, the encoding described in HTTP/2 is recommended instead. The remaining unreserved URI character is ".", but some file system environments do not permit multiple "." in a filename, thus making the "." character unattractive as well.

The pad character "=" is typically percent-encoded when used in an URI, but if the data length is known implicitly, this can be avoided by skipping the padding;