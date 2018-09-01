$e^{πi}$ 表示在单位圆上逆时针旋转180°

* $e^{2πi}$ 逆时针旋转360°的圆
* $t ➜ e^{2πit}$ 随时间 t 运动的圆，1圈/s
* $f ➜ e^{2πift}$ 频率f（旋转速度)，f圈/s
* $e^{-2πift}$ 顺时针旋转
* $g(t)e^{-2πift}$ 缠绕原函数到单位圆
* $∫_{-\infty}^{\infty}g(t)e^{-2πift}dt$ 对称图形的质心
* $G(f) = ∫_{-\infty}^{\infty}g(t)e^{-2πift}dt$
* ${\hat f}(\xi)$ 是 $f(x)$ 的傅里叶变换；$f(x)$ 是 ${\hat f}(\xi)$ 的傅里叶逆变换

## Fourier Transform
$${\hat f}(\xi) = ∫_{-\infty}^{\infty}f(x)e^{-2πix\xi}dx, {\xi}{\in}{\mathbb{R}}  表示频率（HZ） $$

## Inverse Fourier Transform 傅里叶逆变换
$$f(x) = ∫_{-\infty}^{\infty}{\hat f}(\xi)e^{2πix\xi}d{\xi}, x{\in}{\mathbb{R}} $$


## 傅里叶级数
若$f(x)$以$2l$为周期的光滑或分段光滑函数，且定义域为$[-l,l]$，即 $f(x+2l) = f(x)$，则傅里叶级数展开式为：
$$ f(x) = a_{0} + {\sum}_{k=1}^{\infty}(a_{k}cos\frac{k{\pi}x}{l} + b_{k}sin\frac{k{\pi}x}{l})$$
其中，由于以$2l$为周期，则：
$$
a_k = \frac{1}{l}∫_{-l}^{l}f(x)cos\frac{n{\pi}x}{l}dx(n=0,1,2...)
$$
$$
b_k = \frac{1}{l}∫_{-l}^{l}f(x)sin\frac{n{\pi}x}{l}dx(n=1,2,3...)
$$