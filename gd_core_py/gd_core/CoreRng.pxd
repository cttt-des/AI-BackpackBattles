# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class BalancedRng(GodotObject):

    cdef public object _rng
    cdef public object accChance
    cdef public object balancedness
    cdef public object expectedWins
    cdef public object extraLuck
    cdef public object lastResult
    cdef public object lastTarget
    cdef public object wins


from gd_core_py._rt cimport GodotObject


cdef class BalancedRange(GodotObject):

    cdef public object _rng
    cdef public object acc


from gd_core_py._rt cimport GodotObject


cdef class CoreRng(GodotObject):

    cdef public object _stacktrace
    cdef public object debug_flip_tag
    cdef public object draw_seq
    cdef public object globalChainOpen
    cdef public object oracle_trace
    cdef public object oracle_trace_log
    cdef public object rng

