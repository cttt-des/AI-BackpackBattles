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

    cdef public object _activate_countdown
    cdef public object _pending_deferred
    cdef public object _result
    cdef public object _tick_timer_active
    cdef public object _tick_timer_left
    cdef public object activated
    cdef public object combat_time
    cdef public object ctx
    cdef public object fatigue_counter
    cdef public object fatigue_interval
    cdef public object fatigue_next_tick
    cdef public object fatigue_started
    cdef public object fight_ended
    cdef public object max_time
    cdef public object opponent
    cdef public object ordered_items
    cdef public object player
    cdef public object speed_scale
    cdef public object time_advance
    cdef public object timed_out
    cpdef bint hasFatigueStarted(self)
    cpdef bint playerWins(self)

