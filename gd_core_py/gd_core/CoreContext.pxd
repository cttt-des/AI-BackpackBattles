# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class CoreContext(GodotObject):

    cdef public object _deferred
    cdef public bint _drawseq_enabled
    cdef public object _emptyGrid
    cdef public object _timed
    cdef public object below_master
    cdef public object bus
    cdef public object class_resources
    cdef public object combat
    cdef public object combat_log
    cdef public double combat_time
    cdef public object cube_advanced
    cdef public long long cur_mode
    cdef public long long cur_round
    cdef public object custom_health_multiplier
    cdef public object deferred_flush_enabled
    cdef public object eb_relay_mirrored
    cdef public object event_type_keys
    cdef public object fatigueDamageSource
    cdef public bint fight_ended
    cdef public object flk_delay_cursor
    cdef public long long frame_counter
    cdef public object hooks
    cdef public object item_book
    cdef public object keyed_cleanse_biggest_first
    cdef public object keyed_stop_clears_seen
    cdef public object label_rng_enabled
    cdef public object lib_fires
    cdef public bint lobbies_mode
    cdef public object opponent
    cdef public long long out_of_stamina_count
    cdef public object player
    cdef public long long probe_pass
    cdef public object rng
    cdef public object rope_speedups
    cdef public bint sandbag_active
    cdef public object stealLifeDamageSource
    cdef public double time
    cdef public object unhealingDamageSource
    cdef public object util
    cdef public bint warn_unknown_api
    cpdef bint hasDeferred(self)

