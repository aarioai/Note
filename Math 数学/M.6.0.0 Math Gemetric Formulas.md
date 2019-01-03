#  Formulas

## Radian
@see https://en.wikipedia.org/wiki/Radian
1 rad = 1 * 180/?  = 57.2958...


## Arc 
@see http://www.regentsprep.org/regents/math/geometry/gp16/circlesectors.htm
A:Area  C: Circumference

C_circle = 2?r
A_circle = ?r^2

C_sector = 2?r (n/360)
A_sector = (n/360) ?r^2
         = (C_s/2?r) ?r^2

C_seg = 2?r (n/360)
A_seg = A_sector - A_triangle

# Linear Interpolation
Known x in the interval (x0, x1), and y in the interval (y0, y1)
Then
>    dy / dx = (y - y0) / (x - x0)  = (y1 - y0) / (x1 - x0)
>    y = y0 + (y1 - y0)((x - x0) / (x1 - x0))

# Curve 
## B?zier Curve
[B?zier Curve](https://en.wikipedia.org/wiki/B%C3%A9zier_curve)

### Linear B?zier Curves
Known PO(x0, y0), P1(x1, y1), B(t) is line in time t, not a single point
> B(t) = (x,y)(t)= P0 + t(P1 - P0) = (1 - t)P0 + tP1,  time t in [0, 1]
x(t) = (1 - t)x0 + t * x1
y(t) = (1 - t)y0 + t * y1
### Quadratic B?zier Curves
> B(t) = (1 - t)^2 * P0 + 2t(1 - t)P1 + t^2 * P2, t in [0,1]
        ?  P1
       /  B         Point A moves from P0 to P1 ,  point B P1 -> P2
      / ?? \        line AB is always the tangent of the curve
     A ~  ~ \
 P0 ?~      ~? P2 
### Cubic B?zier Curves
> B(t) = (1 - t)^3 * P0 + 3t(1 - t)^2 * P1 + 3 *  t^2 * (1 - t) * P2 + t^3 * P3, t in [0, 1]
                  ?  P1 controlPoint1
                 /           B         ?  endPoint, P2
                /   ? ? ?    ? ?/ 
               A  ?          ?   C
              ? ?                 ?  controlPoint2, P3
    startPoint(using the moveToPoint) P0

Point A moves from P0 to P1, B: P1 -> P2, C: P2 -> P3
Line AB and BC are always the tangent of the curve

> B(t) = ?[i=0, n] C(n, i) * (1 - t)^(n - i) * t^i * P_0
       = (1 - t)^n * P_0 + C(1, n) * (1 - t)^(n - i) * t * P_1 + ...
         ... + C(n - 1, n) * (1 - t) * t^(n - 1) * P_(n - 1) + t^n * P_n
> C(i, n) are the binomial coefficients, C(i, n) = n! / (i! * (n - i)!)


