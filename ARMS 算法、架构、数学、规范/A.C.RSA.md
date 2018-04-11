[RSA](https://en.wikipedia.org/wiki/RSA_\(cryptosystem\))

The RSA algorithm involves four steps: [key generation](#KeyGeneration), [key distribution](#KeyDistribution), [encryption](#Encryption) and [decryption](#Decryption).

# RSA 
RSA involves a public key and a private key. The public key can be known by everyone and is used for encrypting messages. The intention is that messages encrypted with the public key can only be decrypted in a reasonable amount of time using the private key.

The basic principle behind RSA is the observation that it is practical to find three very large positive integers e,d and n such that with modular exponentiation for all m:

```
  (m^e)^d ≡ m mod n
```
and that even knowing e and n or even m it can be extremely difficult to find d.

```


[A' Private Key]



[B' Private Key]
```

## Key Generation      <a id="KeyGeneration"></a>
* Choose two distinct prime numbers p and q.
    - For security purposes, the integers p and q should be chosen at random, and should be similar in magnitude but 'differ in length by a few digits' to make factoring harder. Prime integers can be efficiently found using a primality test.
* Compute n = pq.
    - n is used as the modulus for both the public and private keys. Its length, usually expressed in bits, is the key length.
* Compute φ(n) = φ(p)φ(q) = (p − 1)(q − 1) = n − (p + q − 1), where φ is Euler's totient function. This value is kept private.
Choose an integer e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1; i.e., e and φ(n) are coprime.
Determine d as d ≡ e−1 (mod φ(n)); i.e., d is the modular multiplicative inverse of e (modulo φ(n))
This is more clearly stated as: solve for d given d⋅e ≡ 1 (mod φ(n))
e having a short bit-length and small Hamming weight results in more efficient encryption – most commonly 216 + 1 = 65,537. However, much smaller values of e (such as 3) have been shown to be less secure in some settings.[13]
e is released as the public key exponent.
d is kept as the private key exponent.


## Key Distribution    <a id="KeyDistribution"></a>
To enable Bob to send his encrypted messages, Alice transmits her public key (n, e) to Bob via a reliable, but not necessarily secret route. The private key is never distributed.
## Encryption          <a id="Encryption"></a>
Suppose that Bob would like to send message M to Alice.

He first turns M into an integer m, such that 0 ≤ m < n and gcd(m, n) = 1 by using an agreed-upon reversible protocol known as a padding scheme. He then computes the ciphertext c, using Alice's public key e, corresponding to

```
  c ≡ m^e mod n
```
This can be done efficiently, even for 500-bit numbers, using modular exponentiation. Bob then transmits c to Alice.


## Decryption          <a id="Decryption"></a>
Alice can recover m from c by using her private key exponent d by computing
```
  c ≡ (m^e)^d ≡ m mod n
```