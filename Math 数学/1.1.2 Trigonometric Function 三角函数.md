* $sin(\alpha + \beta) = sin(\alpha)cos(\beta) + cos(\alpha)sin(\beta)$
  
* $sin(t+2{\pi}N) = cos(t)$
* $cos(t+2{\pi}N) = sin(t)$

* $cos(0) = 1 = sin(\frac{1}{2}\pi)$
* $cos(\frac{1}{2}\pi) = 0 = sin(0)$
* $cos(\pi) = -1 = sin(\frac{3}{2}\pi)$

$f(t) = \sum_{k=1}^{n}A_{k}sin(2{\pi}kt  + {\varphi}_k)$, ${\varphi}$ is phase

$Known: sin(2{\pi}kt + {\varphi}_k) = sin2{\pi}kt + cos{\varphi}_k + cos2{\pi}kt + sin{\varphi}_k$

$so, f(t) = \frac{a_0}{2}\sum_{k=1}^{n}(a_{k}cos2{\pi}kt + b_{k}sin2{\pi}kt)$

# Euler Theorem 欧拉公式 #

* $e^{{\pi}i} + 1 = 0$
* $e^{ix} = cosx + isinx, x{\in}{\mathbb{R}}$
* $e^{-ix} = cosx - isinx$
* $cosx = \frac{e^{ix} + e^{-ix}}{2}$
* $sinx = \frac{e^{ix} - e^{-ix}}{2i}$

$cos2{\pi}kt = \frac{e^{2{\pi}ikt} + e^{-2{\pi}ikt}}{2}$

$sin2{\pi}kt = \frac{e^{2{\pi}ikt} - e^{-2{\pi}ikt}}{2i}$

$f(t) = \sum_{k=-n}^{n}C_{k}e^{2{\pi}ikt},C_k$ 是复数，且在[-n,n] 对称，那么总和就是实数

$Symmetry Property: C_{-k} = \bar{C_k}$

$f(t) = ... + C_{m}e^{2{\pi}imt} + ...$

$C_m = f(t)e^{-2{\pi}imt} - \sum_{k{\neq}m}C_{k}e^{2{\pi}i(k-m)t}$

${\int_0^1}C_m{dt} = C_m$，周期为1

${\int_0^1}C_m{dt} ={\int_0^1}f(t)e^{-2{\pi}imt}dt - \sum_{k{\neq}m}C_{k}{\int_0^1}e^{2{\pi}i(k-m)t}$

${\int_0^1}e^{2{\pi}i(k-m)t}dt = \frac{1}{2{\pi}i(k-m)}e^{2{\pi}i(k-m)t}, t{\in}[0,1] = \frac{1}{2{\pi}i(k-m)}(e^{2{\pi}i(k-m)} - e^0) = \frac{1}{2{\pi}i(k-m)}(1 - 1） = 0$

$C_m ={\int_0^1}f(t)e^{-2{\pi}imt}dt$，周期为1

$\hat{f} = {\int_0^1}f(x){e^{-2{\pi}ikx}}dt$，周期为1

$f(x) = {\sum_{k=-n}^n}\hat{f}{C_k}e^{2{\pi}ikx}$