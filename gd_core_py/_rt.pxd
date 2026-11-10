# -*- coding: utf-8 -*-
"""M1-1（2026-11-10）：_rt.py 的类型化伴随声明（手写，勿删）。

设计（docs/性能优化下一步规划.md §4 M1-1）：
  · 本文件只做**声明**——伴随 .pxd 在 Cython 编译 _rt.py 时生效；纯 Python
    运行时（GD_PURE_PY 臂 / 未编译分发）完全忽略本文件，_rt.py 单独运行
    语义逐位不变。
  · 模块级 C 变量（声明在此、赋值在 .py）：PCG32 热路径的掩码/乘数常量。
    声明为 C unsigned long long 后，next_u32 的乘加掩移全程 C u64 运算
    （C 无符号溢出环绕 ≡ Python bigint & MASK64，逐位同果）。
  · cdef class PCG32：state/inc 落 C 槽（.py 里的 class PCG32 是同类的
    定义体）。PCG32 无子类（grep 实证，仅组合使用），无动态属性。
    RandomNumberGenerator.state setter 写入 `int(v) & MASK64` 保证非负，
    对象→u64 收敛安全。

数值安全边界（本项目最贵 bug 类，见规划 §4 M1 闸门）：
  · 不声明 f32/_div/_mod 的签名——它们的输入是对象（int/float/bool 混合），
    签名类型化会在调用边界引入强制转换语义；类型化发生在 .py 体内
    （局部注解 + 常量声明），逐位语义由 seed 20260923≡907 / 42≡1042
    逐位闸把关。
"""

cdef unsigned long long MASK64
cdef unsigned long long UINT32_MAX
cdef unsigned long long PCG_MULT

cdef class PCG32:
    cdef unsigned long long state
    cdef unsigned long long inc
