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

更详细的说明参见[项目 Wiki](https://github.com/weilycoder/attention/wiki/Usage)。

## License

本项目引用了 [Baobaobear/MiniBigInteger](https://github.com/Baobaobear/MiniBigInteger)，其使用了 MIT 许可证，已经复制到相关文件内。但是，**本项目对这些文件有修改，不建议直接引用**；具体修改内容请自行对比。

本项目使用 MIT 许可证，许可证作用范围包括对 MiniBigInteger 项目文件的修改。
