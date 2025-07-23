# Attention

对 [【科普】如何优雅地“注意到”关于e、π的不等式](https://zhuanlan.zhihu.com/p/669285539) 中内容的 C++ 实现。

简单来讲，欲证明 $A + B\alpha\gt 0$，可以构造固定区间上定积分使其结果为 $A + B\alpha$，且被积函数在区间上恒非负。

## Compile

一般来说，将项目所有文件放在同一文件夹下，编译 `solve.cpp` 即可。

推荐的编译选项如下

```bash
g++ solve.cpp -o solve -std=c++17 -O3 -ffast-math
```

## Usage

命令行语法为

```bash
solve <type> <B> <A> [<limit=64>]
```

+ `<type>` 是用于指定类型的字符串；
+ `<B>` 是指定无理数的系数，要求为整数；
+ `<A>` 是常数项系数，要求为整数；
+ `<limit>` 指定尝试构造积分 `<limit>` 次时停止。

目前实现了 $3$ 类积分证明。

输出设计上可以被 Python 的 sympy 解析，如果你希望得到 Latex 版本，可以使用 Python 转换，例如：

```python
import sympy
print(sympy.latex(sympy.sympify(input()).simplify()))
```

项目编写了一个配套的 Python 转换脚本，可以使用

```bash
solve <args...> | python format_output.py
```

### A + B * Pi

例如，欲证明

$$
14885392687-4738167652\pi\gt 0
$$

运行：

```bash
solve pi -4738167652 14885392687
```

输出：

```text
Bounds   : 0, 1
Function : x**23 * (1-x)**23 * (629602886415/653752 + -1184541913/256*x + 116946872953727/20920064*x**2) / (1 + x**2)
```

即

$$
\int_{0}^{1} \frac{x^{23} \left(x - 1\right)^{23} \left(- 116946872953727 x^{2} + 96799580588447 x - 20147292365280\right)}{20920064 \left(x^{2} + 1\right)} \mathrm{d}x
$$

显然积分结果为 $14885392687-4738167652\pi$ 且被积函数在 $[0,1]$ 上恒非负。

### A + B * E

欲证明

$$
193-71\mathrm{e}\gt 0
$$

运行：

```bash
solve e -71 193
```

输出：

```text
Bounds   : 0, 1
Function : x**3 * (1-x)**3 * (1/6 + 0*x) * exp(x)
```

即

$$
\int_{0}^{1} - \frac{x^{3} \left(x - 1\right)^{3} e^{x}}{6} \mathrm{d}x
$$

### A + B * Pi^n

*这里 n 为大于 1 的正整数。*

欲证明

$$
\pi^{3}-31\gt 0
$$

运行：

```bash
solve pi_power_3 1 -31
```

输出：

```text
Bounds   : 0, 1
Function : x**12 * (1091239949453/83203139250 + -240010278547/83203139250*x**2) * ln(1/x)**2 / (1 + x**2)
```

即

$$
\int_{0}^{1} \frac{x^{12} \left(1091239949453 - 240010278547 x^{2}\right) \log{\left(\frac{1}{x} \right)}^{2}}{83203139250 \left(x^{2} + 1\right)} \mathrm{d}x
$$

欲证明

$$
5\pi^{2}-49\gt 0
$$

运行：

```bash
solve pi_power_2 5 -49
```

输出：

```text
Bounds   : 0, 1
Function : x**9 * (395/3 + -325/3*x**2) * ln(1/x)**1 / (1 + x**2)
```

$$
\int_{0}^{1} \frac{5 x^{9} \left(79 - 65 x^{2}\right) \log{\left(\frac{1}{x} \right)}}{3 \left(x^{2} + 1\right)} \mathrm{d}x
$$

### A + B * E^q

*这里 q 为有理数。*

欲证明

$$
\mathrm{e}^{3}-20\gt 0
$$

运行

```bash
solve e_power_3 1 -20
```

输出

```text
Bounds   : 0, 1
Function : x**4 * (1-x)**4 * (75/8 + 21/8*x) * exp(3 * x)
```

$$
\int_{0}^{1} \frac{3 x^{4} \left(x - 1\right)^{4} \left(7 x + 25\right) e^{3 x}}{8} \mathrm{d}x
$$

欲证明

$$
25\exp(-1) - 9 \gt 0
$$

运行

```bash
solve e_power_-1 25 -9
```

输出

```text
Bounds   : 0, 1
Function : x**1 * (1-x)**1 * (1 + 2*x) * exp(-1 * x)
```

$$
\int_{0}^{1} x \left(- 2 x^{2} + x + 1\right) e^{- x} \mathrm{d}x
$$

欲证明

$$
25\exp\left(\dfrac{1}{2}\right) - 41 \gt 0
$$

运行

```bash
solve e_power_1/2 25 -41
```

输出

```text
Bounds   : 0, 1
Function : x**1 * (1-x)**1 * (3/4 + 1/2*x) * exp(1/2 * x)
```

即

$$
\int_{0}^{1} \frac{x \left(- 2 x^{2} - x + 3\right) e^{\frac{x}{2}}}{4} \mathrm{d}x
$$

## License

本项目引用了 [Baobaobear/MiniBigInteger](https://github.com/Baobaobear/MiniBigInteger)，其使用了 MIT 许可证，已经复制到相关文件内。但是，**本项目对这些文件有修改，不建议直接引用**；具体修改内容请自行对比。

本项目使用 MIT 许可证，许可证作用范围包括对 MiniBigInteger 项目文件的修改。
