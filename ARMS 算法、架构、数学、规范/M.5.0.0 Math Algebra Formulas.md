# Matrices
> A(m*n) * B(n*p) = C(m*p), then cij = ai1*b1j + ai2*b2j + .. + ain*bnj
> Matrices A * B * C = A * (B * C)

# Factoring
(a+b)*(c+d) = ac + ad + bc + bd

x^2 - (r+s)x + rs = (x - r)(x - s)
x^2 + 2ax + a^2 = (x + a)^2
x^2 - 2ax + a^2 = (x - a)^2

(a - b)(a + b) = a^2 - b^2
(a - b)(a^2 + ab + b^2) = a^3 - b^3
(a - b)(a^3 + a^2 * b + a * b^2 + b^3) = (a - b)[a^2(a+b) + b^2(a+b)]
                        = (a - b)(a + b)(a^2 + b^2)
                        = (a^2 - b^2)(a^2 + b^2)
                        = a^4 - b^4
(a - b)(a^4 + a^3 * b + a^2 * b^2 + a * b^3 + b^4)

a^n - b^n = (a - b)(a^(n-1) + a^(n-2) * b + a^(n-3) * b^2 + ... + b^(n-1))


a^3 + b^3 = (a + b)(a^2 - ab + b^2)
a^5 + b^5 = (a + b)(a^4 - a^3 * b + a^2 * b^2 - a * b^3 + b^4)
a^n + b^n (n is odd)
          = (a + b)(a^(n-1) - a^(n-2) * b + a^(n-3) * b^2 - ... + b^(n-1))

a^4 + b^4 = (a^2 - sqrt(2ab) + b^2)(a^2 + sqrt(2ab) + b^2

### Sequence of Number
|- A.P. (Arithmetic Progression) -|
the difference between the consecutive terms is constant(common difference)
e.g. 1 3 5 7 9...   an A.P with common difference of 2
an = a1 + (n-1)*d
S_order   = a1 + a2 + a3 .. + an
          = a1 + (a1 + d) + (a1 + 2d) + .. + (a1 + (n-1)d)
S_reverse = (an - (n-1)d) + (an - (n-2)d) .. + an
          = an + (an - d) + (an - 2d) .. + (an - (n-1)d)
```
 [n]
  ∑    (a1 + (i-1)*d) = (S_order + S_reverse) / 2 = (a1 + an)*n / 2
[i=1]
```

|- G.P. (Geometric Progression) -|
each term after the first is found by multiplying the previous one by a fixed, non-zero number called the common ratio. a G.P. is powers r^k
e.g. 2 6 18 54 ... is a G.P. with common radio r = 3
    2*3^0  2*3^1  2*3^2  2*3^3 ...
an = a1 * r^(n-1)
```
 [n]
  ∑   (a1 * r^(i-1)) = a1*(1-r^n)/(1-r)
[i=1]
```

# Derivative
[https://en.wikipedia.org/wiki/Derivative](https://en.wikipedia.org/wiki/Derivative)

[http://web.tongji.edu.cn/~math/bluebird/zsd/n2/z1/z1.htm ](http://web.tongji.edu.cn/~math/bluebird/zsd/n2/z1/z1.htm)

> y = C, y' = 0
> y = Cx + C2, y' = C
> y = x^μ, (x^μ)' = μ * x^(n-1)    (μ: constant)
> y = a^x, y' = a^x * ln_a

y = f(x_0) and dy = f(x_0 + dx) - f(x_0)
```
y = 2x + 1
f'(y) = lim[x->a] (f(x) - f(a)) / (x - a)
      = lim[x->a] ((2x + 1) - (2a - 1)) / (x - a)
      = lim[x->a] (2x + 1 - 2a - 1) / (x - a)
      = 2
e.g. f(x) = x^n (n is unsigned integer), the derivative in x = a is:
    f'(a) = lim[x->a] (f(x) - f(a)) / (x - a)
          = lim[x->a] (x^n - x^a) / (x - a)
          = lim[x->a] (x^(n-1) + a * x^(n-2) ... + a^(n-1))
          = n * a^(n-1)
    f'(x) = n * x^(n-1)
    (x^n)' = n * x^(n-1)
```

> (u ± v)' = u' ± v'
> (uv)' = u'v + uv'
> (u / v)' = (u'v - uv') / v^2


    
f'(x_0) = d
y'' = (y')' = d^2 * y / d * x^2
e.g. 
    y = x^2  then
    y' = 2x, y'' = 2

# Binomial Coefficient
>   C(k, n) = C(k - 1, n - 1) + C(k, n - 1)
>           = n! / (k! * (n - k)!)      k in [0, n]
