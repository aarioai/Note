# Matrix
```
A = [1 2; 3 4]
    |
        1 2
        3 4
    |
A = (1:4)'
    |
        1
        2
        3
        4
    |
A = 1:4
    |
        1 2 3 4
    |
B = repmat(A, 3, 1)
    |
        1 2 3 4
        1 2 3 4
        1 2 3 4
    |
B = repmat(A, 1, 3)
    |
        1 2 3 4 1 2 3 4 1 2 3 4
        
        



A = diag([100 200 300])   % A = 3x3
    |
        100    0    0
          0  200    0
          0    0  300
    |
B = repmat(A, 2)        % B = 6x6
    |
        A A
        A A
    |
C = repmat(A, 2, 3)     % B = 6x9
    |
        A A A
        A A A
    |


```


# Example
```

```



```matlab
x=start:spacing:end
plot($x,$y,[$style,[x2,y2,$style2 ....]]);    % 绘图
plot3($x,$y,$z,[$style])


grid on/off;   
axis(\[$xStart,$xEnd,$yStart,$yEnd, $zStart, $zEnd, $wStart, $wEnd\])      % -inf / inf    坐标范围
axis equal      % x y 坐标间距相等
ezplot('0')     % 画 y=0 坐标，但是这个无法设置 x 范围

x=0:0.001:1
y=zeros(length(r),1)
plot(x,y,'k')                   % 指定范围画 y=0 


set(gca, 'xtick|ytick', $xMin:$step:$xMax)              % 单位刻度
set(gca, 'xticklabel|yticklabel', {'\pi', '2\pi'})      % 命名每个刻度名称

hold on/off                 % 增加新的图形/重置图形
clf                         % 清空画板
figure                      % 增加窗体
title($title)
text($x, $y, $text)         % 往坐标添加文字
```


# Style
```
color:      r(red) g(green) b(blue) y(yellow) k(black) w(white)
point:    +(plus) 0(circle) * . x(cross) s d(diamond) ^ v > < p h
line:       -(solid) --() :(point line) -.()

```

#
```
x=3
y=x^2     // 9

x=-2:1:2 
y=x.^2

sqrt(9)    // 3
sqrt(x)
```