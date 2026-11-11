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
    cdef public object _eng
    cdef public object _left
    cdef public object _multi_start_time
    cdef public object _owner
    cdef public object _seen
    cdef public object _started_frame
    cdef public object _stopped
    cdef public object callback_method
    cdef public object fire_count
    cdef public object multi
    cdef public object name
    cdef public object one_shot
    cdef public object timestamps
    cdef public object wait_time

