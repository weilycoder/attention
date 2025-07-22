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

输出为给定构造的积分表达，例如，记指定的无理数为 $\alpha$，则保证输出的积分结果为 $A + B\alpha$。

目前实现了 $3$ 类积分证明。

输出积分的 Latex 不一定简洁美观，请自行调整。

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

$$
\int_{0}^{1}\dfrac{x^{23}\left(1-x\right)^{23}\left(\dfrac{629602886415}{653752}-\dfrac{1184541913}{256}x+\dfrac{116946872953727}{20920064}x^{2}\right)}{1+x^{2}}\mathrm{d}x
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

$$
\int_{0}^{1}\dfrac{1}{6}x^{3}\left(1-x\right)^{3}\mathrm{e}^{x}\mathrm{d}x
$$

### A + B * Pi^n

欲证明

$$
\pi^{3}-31\gt 0
$$

运行：

```bash
solve pi_power_3 1 -31
```

输出：

$$
\int_{0}^{1}\dfrac{x^{12}\left(\ln x^{-1}\right)^{2}\left(\dfrac{1091239949453}{83203139250}-\dfrac{240010278547}{83203139250}x^{2}\right)}{1+x^{2}}\mathrm{d}x
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

$$
\int_{0}^{1}\dfrac{x^{9}\left(\ln x^{-1}\right)\left(\dfrac{395}{3}-\dfrac{325}{3}x^{2}\right)}{1+x^{2}}\mathrm{d}x
$$

## License

本项目引用了 [Baobaobear/MiniBigInteger](https://github.com/Baobaobear/MiniBigInteger)，其使用了 MIT 许可证，已经复制到相关文件内。但是，**本项目对这些文件有修改，不建议直接引用**；具体修改内容请自行对比。

本项目使用 MIT 许可证，许可证作用范围包括对 MiniBigInteger 项目文件的修改。
