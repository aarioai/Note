# Fermi-Dirac δ Function  狄拉克δ函数
δ函数在除零以外的点上都等于零，且其在整个定义域上的积分等于1。δ函数有时可看作是在原点处无限高、无限细，但是总面积为1的一个尖峰（脉冲），在物理上代表了理想化的质点或点电荷的密度。

https://zh.wikipedia.org/zh-cn/%E7%8B%84%E6%8B%89%E5%85%8B%CE%B4%E5%87%BD%E6%95%B0


$
    \delta(x) = \begin{cases} +\infty, & x = 0 \\ 0, & x \ne 0 \end{cases}
$
且
$
    ∫_{−∞}^{+∞}δ(x)dx=1
$


```matlab
x=-100:0.1:100;
y=dirac(x);         % Dirac function
y=5*sign(y);        % 
plot(x,y);
```

# Fermi-Dirac Distribution 狄克拉分布