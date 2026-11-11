# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class TemporaryStacks(GodotObject):

    cdef public object _amount
    cdef public object item
    cdef public object timeout


from gd_core_py._rt cimport GodotObject


cdef class CoreBuff(GodotObject):

    cdef public object _MAX_STACKS
    cdef public object _current
    cdef public object _nextTemporaryTimeout
    cdef public object _permanentStacks
    cdef public object _resistStacks
    cdef public object _timer_active
    cdef public object _timer_eng
    cdef public object _timer_left
    cdef public object _timer_seen
    cdef public object _type
    cdef public object character
    cdef public object cleanseProtectionChancePercent
    cdef public object ctx
    cdef public object isBuff
    cdef public object reflectChancePercent
    cdef public object resistChancePercent
    cdef public object signalName
    cdef public object temporaryStacks
    cpdef bint isTimerActive(self)

