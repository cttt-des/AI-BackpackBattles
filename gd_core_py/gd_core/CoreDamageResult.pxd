# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2 实例槽位声明）
#
# 本文件把本模块全部顶层类转为 cdef class：实例免 __dict__（每实例
# 一次字典分配）+ 未声明属性赋值编译态报错（形态漂移即时暴露）。
# 基类链必须全部 cdef（GodotObject 见 _rt.pxd 批A）；白名单外的类
# 保持 plain。全部槽位 object 型起步——数值 C 类型（float/int 槽）
# 须先审计该字段的全部赋值域（None/float 混合即炸），逐类放行。
# 引擎补充槽（_PXD_EXTRA_SLOTS）= simulator/gd_core_engine.py 对本类
# 实例的动态赋值面，生成器收集器看不见，必须显式声明。
#
# 修改本类实例属性面（新增 self.X 赋值）后必须重跑生成器同步本文件，
# 否则编译态 AttributeError。tools/gd_to_py.py --check 一并核对。

from gd_core_py._rt cimport GodotObject


cdef class CoreDamageResult(GodotObject):

    cdef public object _ctx
    cdef public object _damage
    cdef public object _damageReduction
    cdef public object _healthDamage
    cdef public object critical
    cdef public object damageSource
    cdef public object event
    cdef public object hit

