# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class CoreItemSort(GodotObject):

    pass


from gd_core_py._rt cimport GodotObject


cdef class CoreCombat(GodotObject):

    cdef public double _activate_countdown
    cdef public bint _pending_deferred
    cdef public object _result
    cdef public bint _tick_timer_active
    cdef public double _tick_timer_left
    cdef public bint activated
    cdef public double combat_time
    cdef public object ctx
    cdef public long long fatigue_counter
    cdef public double fatigue_interval
    cdef public double fatigue_next_tick
    cdef public bint fatigue_started
    cdef public bint fight_ended
    cdef public double max_time
    cdef public object opponent
    cdef public object ordered_items
    cdef public object player
    cdef public double speed_scale
    cdef public double time_advance
    cdef public bint timed_out
    cpdef bint hasFatigueStarted(self)
    cpdef double getEffectiveTime(self)
    cpdef bint playerWins(self)

