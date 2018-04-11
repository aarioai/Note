## Category
*   [Introduction](#Introduction)
    - [Elimination](#Elimination)
*   [Matrices](#Matrices)
    - [Invertible Matrix A^(-1)](#InvertibleMatrix)
    - [Transpose of Matrix A^T](#TransposeOfMatrix)



[Matrix](https://en.wikipedia.org/wiki/Matrix_\(mathematics\))
 * @see https://zh.wikipedia.org/wiki/%E8%A1%8C%E5%88%97%E5%BC%8F
 * @see http://www.tongji.edu.cn/~math/xxds/kcja/kcja_a/01.htm
[］http://www2.edu-edu.com.cn/lesson_crs78/self/j_0022/soft/ch0605.html
 */


# Introduction <a id="Introduction"></a>
```
Known:
    2x - y = 0
    -x + y = 3
```
### Row Picture Solution: 
```
            |        /⁄
            |       • (3, 6) 
            |     ⁄/
            |   ⁄ /
            | ⁄  /  2x - y = 0
 -x + y = 3 ⁄   /
           ⁄|  /
         ⁄  | /
       ⁄    |/
––––– ⁄–––––o–––––––––––––––––––––>
    ⁄      /|
          / |
```

Column Picture Solution:

```
Solve: 
    [2 -1]   [x]    [0]
    [-1 1] * [y]  = [3]     Matrix A * Vector χ  = b

        [2]         [-1]      [0]
    x * [-1]  + y * [1]   =   [3]

VectorA(x * (0,0->2,-1))  +  VectorB (y * (0,0->-1,1))  = VectorC(0,0->0,3)
```


```
Known:
    x + y + z = 3
    2x - y - z = 2
    -x + z = 4    
```

Row Picture

The three planes cross one point which is the solution.

```     
                        Z
                        |
                        |
                        |
                        +---------------Y
                       /
                      /
                     /
                    X

```
Column Picture Solution

```

    [ 1  1  1]   [x]    [3]
    [ 2 -1 -1] * [y]  = [2]    Matrix A * Vector χ = b
    [-1  0  1]   [z]    [4]

        [ 1]         [ 1]         [ 1]     [3]
    x * [ 2]  +  y * [-1]  +  z * [-1]  =  [2]
        [-1]         [ 0]         [ 1]     [4]

    ->     ->    ->     ->
    a   +  b  +  c   =  d
```

>  Aχ  = b, A is a Matrix, χ is a Vector,   Aχ  is a combination of column S

```
[2 5]     [1]        [2]        [5]      [12]
[1 3]  *  [2]  = 1 * [1]  + 2 * [3]   =  [7]
               
               = [2*1+2*5] = [12]
                 [1*1+3*2]   [7]

```



### Elimination <a id="Elimination"></a>

```
Known:
     x + 2y + z = 2
    3x + 8y + z = 12
         4y + z = 2

Solve:
    Convert it into Aχ = b
                [1• 2 1]              [x]             [ 2]
    Matrix A =  [3  8 1]   Vector χ = [y]  Vector b = [12]
                [0  4 1]              [z]             [ 2]
    
    • is the First Privot, the first row is the Privot Row
    Let's eliminate x , eliminate the privot row multiplice 3 from row 2
    
    [1 2   1]
    [0 2° -2]    // ° is the 2nd Privot (2 is not zero)
    [0 4   1]
    
       
    [1• 2   1 ]
    [0  2° -2 ]
    [0  0   5·]   // · is the 3rd Privot (5 is not zero)


    [1 2 1  2]    [1• 2  1 2]    [1• 2   1    2]
    [3 8 1 12] => [0  2 -2 6] => [0  2° -2    6]
    [0 4 1  2]    [0  4  1 2]    [0  0   5· -10]

    Now get
        x + 2y + z  = 2
            2y - 2z = 6 
                 5z = -10
                 
```


> Privot must be non-zero




# Matrices <a id="Matrices"></a>

# Linear Transformations

```
    E---I-------------------• C(a+c, b+d)
    |   |                  /|
    G---• D(c,d)          / |  
    |  /                 /  |   
    |-/---------B(a, b)-•   J    
    |/                  |   |
  A •-------------------H---F-------

Analyze:
    S_square_1 = S_triangle_ADG + S_triangle_BJC
    S_square_2 = S_triangle_IDC + S_triangle_AHB
    
    S_parallelogram_ABCD = S_ACEF - S_square_1 - S_square_2 
                        - S_square_EGDI - S_square_BHJF
        = (a+c) * (b+d) - a*b - c*d - c*b - c*b
        = ab + ad + cb + cd - ab - cd - 2*cb
        = ad - cb

        [a c]
    A = [b d] 

    S_parallelogram = |A| = ad - cb

```



## Matrix Mulplication <a id="MatrixMulplication"></a>
```
    [3]   
A = [5]            m * 1      a Column Vector
    [7]

    
A = [3 5 7]          1 * n    a Row Vector




```
### Matrix Muliplicates a Vector
```
[v1]     [a11 a12 a13]
[v2]  *  [a21 a22 a23]
[v3]     [a31 a32 a33]
    (1)     
                [a11]           [a12]          [a13]
        =  v1 * [a21]   +  v2 * [a22]  +  v3 * [a23]
                [a31]           [a32]          [a33]

    (2)
           [v1*a11 + v2*a12 + v3*a13]
        =  [v1*a21 + v2*a22 + v3*a23]
           [v1*a31 + v2*a32 + v3*a33]
           
             [a11 a12 a13]   
[v1 v2 v3] * [a21 a22 a23] = v1*[a11 a12 a13] + v2*[a21 a22 a23] + v3[a31...
             [a31 a32 a33]

```
>                                               [n]
> [AB]i,j = ai1*b1j + ai2*b2j + .. + ain*bnj =   ∑   Ai,r * Br,j
>                                              [r=1]A
> A(m*n) * B(n*p) = C(m*p), then cij = ai1*b1j + ai2*b2j + .. + ain*bnj

```
e.g. 
  [1 2]    [5 6]       [1*5+2*7 1*6+2*8]   [19 22]
  [3 4] *  [7 8]   =   [3*5+4*7 3*6+4*8] = [43 50]
  
  [5 6]   [1 2]       [5*1+6*3 5*2+6*4]     [23 34]
  [7 8] * [3 4]   =   [7*1+8*3 7*2+8*4] =   [31 46]

so A * B may not equal B * A  


Known:  
          [1 2 1]   [1• 2  1]
    E21 * [3 8 1] = [0  2 -2]  (Elementary Matrix Elimination a21->0) 
          [0 4 1]   [0  4  1]

Solve:
    If the line in the mulpilicated matrix is same as the same line in one of the multiplier, keep the Prior to 1, and other columns to 0.
    
         [1    0   0 ]   
   E21 = [a21 a22 a23]
         [0    0   1 ]
    a21 * 1 + a22 * 3 + 0     = 0      --> a21 = -3*a22
    a21 * 2 + a22 * 8 + a23   = 2
    a21     + a22     + a23   = -2     --> a23 = 2*a22 - 2
    
So:
          [ 1  0 0]
    E21 = [-3  1 0] 
          [ 0  0 1]


Known:
          [1• 2  1]   [1• 2   1]
    E32 * [0  2 -2] = [0  2° -2] (Elimination 32 -> eliminate a32 to 0)
          [0  4  1]   [0  0   5]

          [1  0 0]
    E32 = [0  1 0]
          [0 -2 1]




    E32 * (E21 * A) = U
    (E32 * E21) * A = U
```

> Matrices   A * B * C = A * (B * C)






```
        [2]    [1*2+6*2]   [14]
[1 6] * [3] =  [1*3+6*3] = [21]
        [4]    [1*4+6*4]   [28]
        
[2]           [2 12]
[3] * [1 6] = [3 18]
[4]           [4 24]


[2 3 4]   [0 1000]    [2*0+3*1+4*0 2*1000+3*100+4*10]   [3 2340]
[1 0 0] * [1 100 ]  = [1*0+0*1+0*0 1*1000+0*100+0*10] = [0 1000]
          [0 10  ]
          
[0 1000]   [2 3 4]    [1000 0 0]
[1 100 ] * [1 0 0] =  [102  3 4]
[0 10  ]              [10   0 0]


[2 3]   [1 8]     [2]            [3]
[4 5] * [9 0] =   [4] * [1 8] +  [5] * [9 0]
[6 7]             [6]            [7]

```

## Inverse
[Invertible Matrix](https://en.wikipedia.org/wiki/Invertible_matrix)

> Non-square matrices do not have an inverse. 
> Not all square matrices have inverse
> If A is invertible, then |A| != 0

> If A's inverse A^(-1) exists, then 
>   A^(-1) * A = I = A * A^(-1)
>   (kA)^(-1) = k^(-1) * A^(-1) for nonzero scalar k
>   (A^T)^(-1) = (A^(-1))^T

> AI = A

> A,B are all invertible matrix. Then
>   ABB^(-1)A^(-1) = A(BB^(-1))A^(-1) = AIA^(-1) = AA^(-1) = I
>   B^(-1)A(-1)AB = B^(-1)IB = I

> If square matrices AB = I or BA = I, then A is invertible, B = A^(-1)
> A matrix that is its own inverse, i.e. A = A^(-1) and A^2 = I, is called an involution

> The adjugate of a invertible matrix A can be used to find A^(-1)
>              1
>   A^(-1) = –––––  adj(A)
>            det(A)

```
[1 0 0 ...]
[0 1 0 ...]
[0 0 1 ...]    Identity Matrix (I)
[........1]

```

### Singular Matrix (Degenerate or Non-Invertible)
> A square matrix is singular if and only if its determinant is 0.
> I can find the matrix by a a vector X with Ax = 0, (x != 0), this matrix is singular matrix.


```
    
    [1 4]           [0]         ->
    [2 8]  *  x  =  [0] ,  x != 0
    
    Then
             [-4]    [ 4]
        x =  [ 1] or [-1]   or ...
        
    So this matrix is not invertible

 ```    
### Gauss-Jordan ( Solve 2 equations at once)

> A * column j of A^(-1) equals column j of I

```
    [1 3]    [a c]   [1 0]
    [2 7] *  [b d] = [0 1]

    [1 3]   [a]   [1]
    [2 7] * [b] = [0]

    [1 3]   [c]   [0]
    [2 7] * [d] = [1]

    [1 3 1 0]   
    [2 7 0 1]           [A | I]
    
      [1• 3  1 0]
    = [0  1 -2 1]                   by elimination
    
      [1 0   7 -3]
    = [0 1° -2  1]    [I | A^(-1)]  by elimination
     

     Check
        [1 3]   [7 -3]   [1 0]    [7 -3]   [1 3]
        [2 7] * [-2 1] = [0 1]  = [-2 1] * [2 7]
     
```
### Gaussian Elimination


# Transpose
[Transpose](https://en.wikipedia.org/wiki/Transpose)

```
[\1  3]                           [\1  2]
[ 2 \4]  A    ========    A^T =   [ 3 \4]

[\1  3  5]                           [\1  2]
[ 2 \4  6]   A     ========   A^T =  [ 3 \4]
                                     [ 5  6]

```
> (A^T)<ij> = A<ji>
> (A^T)^T = A
> (A + B)^T = A^T + B^T
> (AB)^T = B^T * A^T      // @note the order of the factors reverses

>   (A^(-1))^T * A^T = I     (A^(-1))^T : inverse of A transpose



### Symmetric Matrix: A^T = A    <a id="SymmetricMatrix"></a>
> A^T * A is always symmetric
```
Prove:
    (A^T * A)^T  = (A^T)^T * A^T  = A * A^T
    so A^T * A is alwyas symmetric

[\1  3  5]    [\1  2]   [35  44]
[ 2 \4  6] *  [ 3 \4] = [44  56]
              [ 5  6]   

```
### Skew-Symmetric Matrix: A^T = -A     // whose pivots are all 0
### Hermitian Matrix: A^T = 
### Orthogonal Matrix: A^T = A^(-1)
```
  
      [3 2]    [3• 2] 
E21 * [9 7]  = [0  1]       EA = U

      [ 1 0] 
E21 = [-3 1] 

    [1 0 ....]        [1 x x ... x]
L = [x 1 0 ..]    U = [0 1 x ... x]
    [x x 1 ..]        [0 0 1 x . x]


[3 2]       [3• 2]
[9 7] = L * [0  1]         A = LU

         [1 0]                    [ E11 E12]
     L = [3 1] ＝ E21^(-1)    ==> [-E21 E22]   



[3 2]         [1 0]   [3• 2]   [1 0]   [3 0]   [1 2/3]
[9 7] = L U = [3 1] * [0  1] = [3 1] * [0 1] * [0 1  ] = LDU   




Suppose A is a 3-by-3 matrix, 
    E32 * E31 * E21 * A = U (no row exchange)
    A = E21^(-1) * E31^(-1) * E32^(-1) * U







Assume:
      [a11 a12 ... a1n]           [x1]        [b1]
  A = [...            ]       X = [..]    B = [..]
      [am1 am2 ... amn]           [xn]        [bm]
  
  a11*x1 + a12*x2 .. a1n*x1 = b1
  ...
  am1*x1 + am2*x2 .. amn*xn = bm
  
  Then AX = B

  
The transpose of an m-by-n matrix A is the n-by-m matrix A^T

                    [a11 a12 .. a1m]
(A^T)m,n = A n,m =  [...           ]
                    [an1 an2 .. anm]

Then:                   
  1.  (A^T)^T = A
  2.  (A+B)^T = A^T + B^T
  3.  (λA)^T = λA^T
  4.  (AB)^T = B^T A^T

E.g.
   A =  [3 1]     C = [1 -0.5]    
        [4 2]         [-2 1.5]
  Then
    AC =  [1 0]       CA = [1 0]
          [0 1]            [0 1]
  

```

## Permutation
```
      [a11 a12]   [a21 a22]
  P * [a21 a22] = [a11 a12]   Exchange two rows
    
      [0 1]
  P = [1 0]
    
  [a11 a12]       [a12 a11]
  [a21 a22] * P = [a22 a21]   Exchange two columns
      
      [0 1]
  P = [1 0]         @notice now P is on the right side of this mulplication





```

P: execute row exchanges


> PA = LU     any invertible A;  P is identity matrix with reordered rows


> P^(-1) = P^T





# Vector Spaces <a id="VectorSpaces"></a>

->                  ->
a = (3,1 -> 5,5)    b  = (3,1 -> 2,4)

Move them to start from (0, 0)

->'                ->'
a  = (0,0 -> 2,4)  b   = (0,0 -> -1,3)

->'   [2]    ->'   [-1]
a   = [4]    b   = [ 3]


->  ->    ->'   ->'   [2]   [-1]   [1]
a + b   = a  +  b   = [4] + [ 3] = [7]








```
A = [a11]   |A| = a11                1x1 Square Matrix 


    [a11 a12]
A = [a21 a22]     |A| = a11 * a22 - a12 * a21


    [a11 a12 a13]
A = [a21 a22 a23] 
    [a31 a32 a33]   

                [a22 a23]           [a12 a13]           [a12 a13]
    |A| = a11 * [a32 a33]  -  a21 * [a32 a33]  +  a31 * [a22 a23]

        = a11*a22*a33 - a11*a23*a32 - a21*a12*a33 + a21*a13*a32
            + a31 * a12 * 23 - a31 * a13 * a22
    
        = a11*a22*a33 + a21*a32*a13 + a31*a12*a23
            - a31*a22*a13 - a21*a12*a23 - a11*a32*a23

    [a11 a12 a13 a14]
    [a21 a22 a23 a24]
A = [a31 a32 a33 a34]
    [a41 a42 a43 a44]
    
                [a22 a23 a24]         [a12 a13 a14]
   |A| = a11 *  [a32 a33 a34] - a21 * [a32 a33 a34]
                [a42 a43 a44]         [a42 a43 a44]
        
                [a12 a13 a14]         [a12 a13 a14]
         + a31* [a22 a23 a24] - a41 * [a22 a23 a24]
                [a42 a43 a44]         [a32 a33 a34]


|A| = det(A) = ∑[σ∈Sn]sgn(σ)[n]T[i=1]Xi,σ(i)  
 
                   [a11 a12 .. a1n]   
                   [a21 a22 .. a2n]   
A = det(A) = |A| = [...           ]   ∈ R^m*n          a Square Matrix
                   [...           ]
                   [am1 am2 .. amn]



```

```
e.g.
Known:
                              [ a  b  0 ]
    Point(x, y) transforms by [ c  d  0 ], get the transformed P(x', y')
                              [ tx ty 1 ]

Analyze:
                          [ a  b  0 ]
    [x' y' 1] = [x y 1] * [ c  d  0 ]
                          [ tx ty 1 ]
    x' = ax + cy + tx
    y' = bx + dy + ty

Solution:
    c11 = xa + yc + 1*tx    =  ax + cy + tx
    c12 = xb + yd + 1*ty    =  bx + dy + ty
    c13 = x*0 + y*0 + 1*1   =  1

```


