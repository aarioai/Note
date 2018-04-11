# Primality Test

[Prime Number](https://en.wikipedia.org/wiki/Prime_number)

[Primality Test](https://en.wikipedia.org/wiki/Primality_test)

## Testing primality and integer factorization

Indeed, if n = a * b is composite (with a and b ≠ 1) then one of the factors a or b is necessarily at most √n.


The simplest primality test is trial division: Given an input number n, check whether any prime integer m from 2 to √n evenly divides n (the division leaves no remainder). If n is divisible by any m then n is composite, otherwise it is prime.

```c
bool isPrime(int n) {                 // O(√n)
  if (n <= 1) 
    return false;
  else if (n <=3)
    return true;
  double sqrt_n = sqrt(n);
  int i = 2;
  for (i; i <= sqrt_n; i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}

bool isPrime(int n) {
  if (n <= 1) 
    return false;
  else if (n <=3)
    return true;
  else if (n % 2 == 0 || n % 3 == 0)
    return false;
    
  int i = 5;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i+2) == 0)
      return false;
  }
  return true;
}

```


# Modular Exponentiation
[Modular Exponentiation](https://en.wikipedia.org/wiki/Modular_exponentiation)

```
c ≡ x (mod m)    ===>  c mod m == x .
  e.g  7 ≡ 0 (mod 7)     7 ≡ -1 (mod 8)
  

```

```
The operation of modular exponentiation calculates the remainder when an integer b (the base) raised to the eth power (the exponent), be, is divided by a positive integer m (the modulus). In symbols, given base b, exponent e, and modulus m, the modular exponentiation c is: c ≡ b^e (mod m).

```

Modular exponentiation can be performed with a negative exponent e by finding the modular multiplicative inverse d of b modulo m using the extended Euclidean algorithm. That is:
```
c ≡ b^e ≡ d^(−e) (mod m) where e < 0 and b ⋅ d ≡ 1 (mod m).
```

## Straghtforward Method to Solve Modular Exponentiation
The most straightforward method of calculating a modular exponent is to calculate be directly, then to take this number modulo m. Consider trying to compute c, given b = 4, e = 13, and m = 497:
```
c ≡ 4^13 (mod 497)   ,  c = 445
```

```
typedef unpredibleBigint int
int modularPow(int b, int e, int m) {       // O(e) + Memory-Cost
  int c;
  unpredibleBigint be = 1;                // it may takes much memory space                 
  for (int ei = 0; ei < e; ei++) {
    be *= b;
  }
  c = be % m
  return c;
}
```

The time required to perform the exponentiation depends on the operating environment and the processor. The method described above requires O(e) multiplications to complete.

## Memory-Efficient Method to Solve Modular Exponentiation
A second method to compute modular exponentiation requires more operations than the first method. Because the required memory is substantially less, however, operations take less time than before. The end result is that the algorithm is faster.
This algorithm makes use of the fact that, given two integers a and b, the following two equations are equivalent:
```
b^e mod m = (x * y) mod m
b^e mod m = [(x mod m)  * (y mod m)] mod m

b^e mod m = (b * b * ... * b) mod m
          = (b mod m) * b * b ...) mod m
          = (((b mod m) * b) mod m * b ... ) mod m
```

```c
int modularPow(int b, int e, int m) {       // O(e)
  int c = 1;
  for (int ei = 0; ei < e; ei++) {
    c = (b * c) % m;
  }
  return c;
}


(b * (b * ... (b * ?) % m ) % m ) %m
```
## Right-To-Left Binary Method
A third method drastically reduces the number of operations to perform modular exponentiation, while keeping the same memory footprint as in the previous method. It is a combination of the previous method and a more general principle called exponentiation by squaring (also known as binary exponentiation).
First, it is required that the exponent e be converted to binary notation. That is, e can be written as:
```
    n-1
e =  ∑   a_i * 2^i   , a_i can take the value 0 or 1. By definition, a_n − 1 = 1.
    i=0
 
e.g.   10  ==>  binary `1010` 
    
Known: 
  x^(a * b) = (x^a)^b
  x^(a + b) = x^a * x^b
          ( n-1         )    n-1
  b^e = b^(  ∑ a_i * 2^i)  =  Π   (b^(2^i))^a_i
          ( i=0         )    i=0
        
So:
      n-1
  C ≡  Π   (b^(2^i))^a_i  (mod m)
      i=0
```
```c
int modularPow(int b, int e, int m) {       // O(log e)
  int c = 1;
  while (e > 0) {
    if (e % 2 == 1)
      c = (c * b) % m;
    e >> 1;
    b = (b * b) % m;
  }
  return c;
}
```

## Matrices Method
The Fibonacci numbers and Perrin numbers modulo n can be computed efficiently by computing Am (mod n) for a certain m and a certain matrix A. The above methods adapt easily to this application. This can be used for primality testing of large numbers n, for example. Pseudocode:

A recursive algorithm for ModExp(A, b, m) = A^b (mod m), where A is a square matrix.
```c
int matrixModPow(Matrix A, int b, int m) {
  if (b % 2 == 1)
    return (A *　matrixModPow(A, b - 1, m)) % m;
  Matrix D = matrixModPow(A, b / 2, m);
  return (D * D) % c;
}
```

# Fermat's Little Theorem
[Fermat's Little Theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)

Fermat's little theorem states that if p is a prime number, then for any integer a, the number a^p − a is an integer multiple of p.
```
a^p ≡ a (mod p)


a^(p - 1) ≡ 1 (mod p)    ,  a is not divisible by p
```

> If p is a prime and a is any integer not divisible by p, then a p - 1 - 1 is divisible by p.

Fermat's little theorem is a special case of Euler's theorem: for any modulus n and any integer a coprime to n, we have

```
a^(φ(n)) ≡ 1 (mod n)
```
where φ(n) denotes Euler's totient function (which counts the integers between 1 and n that are coprime to n). Euler's theorem is indeed a generalization, because if n = p is a prime number, then φ(p) = p − 1.

## Usage
Calculate the modular of 2^100 divides 13
```
According to Fermat's Little Theorem
  a^(p - 1) ≡ 1 (mod p)
Which means:
  2^12 ≡ 1 (mod 13)
Then
  2^100 = 2^(12 * 8 + 4) = (2^12)^8 * 2^4
  (2^12)^8 * 2^4 / 13 = 1^8 * 2^4 / 13 = 2^4 / 13 = 16 / 13 = 1..3
```




# Euler's Totient Function
[Euler's Totient Function](https://en.wikipedia.org/wiki/Euler%27s_totient_function)

Euler's totient(φ) function counts the positive integers up to a given number n that are relatively prime to n. e.g. φ(9) = 5 (1, 2, 5, 7, 8). It can be defined more formally as the number of integers k in the range 1 ≤ k ≤ n for which the greatest common divisor gcd(n, k) = 1.

## Computing Euler's Totient Function
There are several formulas for computing φ(n). 

### Euler's Product Formula
* For any a prime number p, φ(p) = p - 1

* The function φ(n) is multiplicative, this means that if gcd(m, n) = 1, then φ(mn) = φ(m) φ(n).

* φ(p^k) = p^k − p^(k−1) = p^(k−1) * (p − 1) = p^k * (1 - 1/p)   , k >= 1
```
Proof:
  Since p is a prime number the only possible values of gcd(p^k, m) are 1, p, p^2, ..., p^k, and the only way for gcd(p^k, m) to not equal 1 is for m to be a multiple of p. The multiples of p that are less than or equal to p^k are p, 2p, 3p, ..., (p - 1) * p, p^2, 2 * p^2 ..., (p-1) * p^(k-1), p * p^(k-1)  and there are p^(k−1) of them. Therefore, the other p^k − p^(k−1) numbers are all relatively prime to p^k.
```

```
φ(n) = n  Π  (1 - 1/p)
         p|n       
```

I














































