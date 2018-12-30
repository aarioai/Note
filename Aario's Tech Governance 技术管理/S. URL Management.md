## Catalog 目录
*   [Access Tokens](#AccessTokens)
# Access Tokens <a id="AccessTokens"></a>
[Facebook Access Tokens](https://developers.facebook.com/docs/facebook-login/access-tokens)

## Pros and Cons To Response Expire And ExpireAt
```
Server: Generate token, expire 86400 (at 2016-07-02 00:00:00 -0800)
{
    "access_token" : "ACCESS_TOKEN},
   // "expire" : 86400,             // a day
    "expire_at" : "2016-02-03 00:00:00 -0800"     //    -- ISO 8601 format
}

Client: receives , expire 86400 s( 1day), now 2016-02-02 00:00:02 -0800
```



## User Access Token

Regenerate an access token once re-visit this url;

```
GET /oauth2/access_token?client_id={username}&client_secret={password} & grant_type=client_credential
{
    "access_token" : "ACCESS_TOKEN},
   // "expire" : 7200,
    "expire_at" : "2020-02-03 14:15:29 -0100"     //    -- ISO 8601 format
}
```


## App Access Token
```
GET /oauth2/access_token?
    client_id={client-id}
    & client_secret={client-secret}
    & grant_type=client_credential
```
    
Response

```json
{
    "access_token" : "ACCESS_TOKEN},
    "expire" : 7200             // Wechat keeps it alive for 7200 sec
}
```

Therefore, this API call should only be made using server-side code.
Again, for security, app access token should never be hard-coded into client-side code

There is another method to make calls API that doesn't require using a generated app access token
```
GET /api?access_token={app-id}|{app-secret}
```

### Page Access Token
### Client Token
