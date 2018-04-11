# Uniform Services
For security, check app key and token as possible

```
Params:
    app_key = ${app key}
    access_token = ${access token}
GET 
    standard/access_token : string       // get access token
    standard/time                        // adjust time
```


# Signature for Products
```
      --(1)--> standard/timestamp
  APP --(2)--> cart/app_key=${app key}&sign=CSDDES203D...&params=${values}  
  
```

encrypt()    --> md5() or sha2()

APP: app_key(public)  + secret_key(private)

[Secret Key](https://en.wikipedia.org/wiki/Key_\(cryptography\))

values of params:
    e.g. product_id=110&amount=1&price=188.81&buy_type=payments_by_instalments
    `1101188.81payments_by_instalments`

encrypt(Timestamp + secret_key + values of params + app_key)


