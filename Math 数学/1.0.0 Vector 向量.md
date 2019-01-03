orthogonal  正交

向量一般用于表示点的运动，即包含这个点潜在变化方向和大小。因此平移向量不会改变向量值（即方向、大小）。$\vec{a}$ = $\vec{AB}$ = $\vec{OC}$  可以位移到原点。

![vector](https://github.com/AarioAi/Note/blob/master/ARMS%20Math%20and%20Matlab%20%E6%95%B0%E5%AD%A6/_asset/vector--2-5.jpg?raw=true)

## 向量运算

### Scalar Addition 标量运算
即向量和常量运算

![scalar addition](https://github.com/AarioAi/Note/blob/master/ARMS%20Math%20and%20Matlab%20%E6%95%B0%E5%AD%A6/_asset/vector-scalar-addition.png?raw=true)

### Vector Addition

![vector addition](https://github.com/AarioAi/Note/blob/master/ARMS%20Math%20and%20Matlab%20%E6%95%B0%E5%AD%A6/_asset/vector-addition.jpg?raw=true)

在numpy的中，如果向量是一维的，那么他就能看作是一个标量，与其他多维向量的运算就相当于一个数。

```python
y = np.array([1,2,3])
x = np.array([2,3,4])
y + x = [3, 5, 7]
y - x = [-1, -1, -1]
y / x = [.5, .67, .75]
```

### Cross Product 向量积

向量的乘法有两种类型：**Dot Product（点积）**和阿达玛积。其中向量和矩阵的dot product是深度学习的重要运算。

$$\vec{a} * \vec{b} = \vec{OA} * \vec{OB} = x_1x_2 + y_1y_2$$

$$\vec{a} * \vec{b} = \sum{_{i=1}^n}a_ib_i$$

> 两个单位向量的点积越大，表明两者越相似。
>> 因为点积就是余弦距离，越大夹角越接近于0。这个是点积本身的性质，在二维空间，点积可以想象成一条直线在另一条直线上的投影。点积为0表示相互垂直。