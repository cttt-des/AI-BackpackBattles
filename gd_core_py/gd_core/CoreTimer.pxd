# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class CoreTimer(GodotObject):

    cdef public object _ctx
    cdef public object _dbg
    cdef public double _eng
    cdef public double _left
    cdef public double _multi_start_time
    cdef public object _owner
    cdef public double _seen
    cdef public long long _started_frame
    cdef public bint _stopped
    cdef public object callback_method
    cdef public long long fire_count
    cdef public bint multi
    cdef public object name
    cdef public bint one_shot
    cdef public object timestamps
    cdef public double wait_time
    cpdef bint is_stopped(self)
    cpdef double get_time_left(self)
    cpdef bint isFinished(self)
    cpdef double _utilTime(self)

