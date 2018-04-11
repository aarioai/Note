package cookietest

import (
	"net/http"
	"time"
)

type Cookie struct {
	Res http.ResponseWriter
	Req *http.Request
}

func (c *Cookie) GetQueryKey() string {
	k := c.Req.URL.Query().Get("key")
	if k == "" {
		k = "test"
	}
	return k
}

func (c *Cookie) Set(k string, v string) {
	expires := time.Now().AddDate(0, 0, 1)
	cookie := http.Cookie{Name: k, Value: v, Path: "/", MaxAge: 86400, Expires: expires}
	http.SetCookie(c.Res, &cookie)
}

func (c *Cookie) Get(k string) (*http.Cookie, error) {
	return c.Req.Cookie(k)
}
