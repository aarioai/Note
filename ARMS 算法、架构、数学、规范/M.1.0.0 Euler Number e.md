## Category 目录
*   [The Physical Meaning of e](#ThePhysicalMeaningOfE)
*   [Prove e less than 3](#ProveELessThan3)

[Euler's Number](https://en.wikipedia.org/wiki/E_\(mathematical_constant\))

```
        ∞
    e = ∑  (1 / n!) = lim (1 + 1/n)^n ≈ 2.71828...
       n=0            n→∞
```

# The Physical Meaning of e   <a id="ThePhysicalMeaningOfE"></a>

[The Physical Meaning of e](https://www.math.toronto.edu/mathnet/answers/ereal.html)

## The Interest on Debt

If a $100 account earns 5% simple interest annually, the balance remains at $100 and this year's interest payment is $5.

If a $100 account earns 5% yearly compound interest semiannually, now the balance remains:

```
    100                                 principal
    --> (1 + 1/2 * 5%) * 100            semiannual
    --> (1 + 1/2 * 5%)^2 * 100          annual
```

Earns quartly:

```
    100
    --> (1 + 1/4 * 5%) * 100
    --> (1 + 1/4 * 5%)^2 * 100
    --> (1 + 1/4 * 5%)^3 * 100
    --> (1 + 1/4 * 5%)^4 * 100
```

Earns quickly (monthly, dayly, .. secondly...) :

```
    (1 + 1/n * interest)^n * principal

    If interest less than 1, then
        1/n * interest less than 1/n
        (1 + 1/n * interest)^n  less than (1 + 1/n)^n   n > 0
```

> The balance under compound interest will less than e * principal, if the interest < 1



### Prove e < 3     <a id="ProveELessThan3"></a>

* 0! = 1
* If an = a1 * q^(n-1), then   Sn = a1 * (1 - q^n) / (1 - q)
* a^n - b^n = (a - b)[a^(n-1) + a^(n-2) * b + ... + a*b^(n-2)+b^(n-1)] 

```
        ∞
    e = ∑    = 1/0! + 1/1! + 1/2! + ... + 1/n!
       n=0
 
    1/(s!) = 1 * 1/2 * 1/3 * ... * 1/s
      < 1 * 1/2 * 1/2 * ... * 1/2 = 1/(2^(s-1))

     So
        e < 1 + 1 + 1/2 + 1/(2^2) + ... + 1/2^(n-1)
            = 1 + (1 - (1/2)^n) / (1 - 1/2)
            = 1 + (1 - (1/2)^n) / (1/2)
            = 1 + 2 * (1 - (1/2)^n)
            < 1 + 2 * (1 - 0)
            = 3
```
