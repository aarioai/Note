https://zh.wikipedia.org/wiki/%E5%8D%B7%E7%A7%AF

卷积是一个积分，反映一个函数f(t)在另外一个函数g(t)移动时所重叠的量。

函数 f,g 是 $\mathbb{R}^n$ 上可测函数（Measuable function），f与g的convolution记作 f*g，即：
$$ (f*g)(t) ≡ ∫_{\mathbb{R}^n}f(τ)g(t-τ)dτ = ∫_{\mathbb{R}^n}f(t-τ)g(τ)dτ = (g*f)(t) $$

1. τ 表示时间变量，非常数
2. 函数 f(τ),g(τ)，将g(τ)右移t单位，得到函数g(τ-t)
3. 将g(τ-t)做x轴对称翻转得到-g(τ-t)，即g(t-τ)
4. 时间变量τ变化，两函数就会交汇，计算交汇面积。

对卷积微分，可用于图像边缘抽取。
$$ \frac{d}{dx}(f*h) = \frac{df}{dx}*h = f*\frac{dh}{dx} $$

# 离散卷积 Discrete Convolution
f(x),g(x) 定义域在整数$\mathbb{Z}$，卷积定义：
$$ （f*g)[n] ≡ \sum_{m=-\infty}^{\infty}f[m]g[n-m] = \sum_{m=-\infty}^{\infty}f[n-m]g[m] $$