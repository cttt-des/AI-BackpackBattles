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


cdef class CoreContext(GodotObject):

    cdef public object _deferred
    cdef public object _drawseq_enabled
    cdef public object _emptyGrid
    cdef public object _timed
    cdef public object below_master
    cdef public object bus
    cdef public object class_resources
    cdef public object combat
    cdef public object combat_log
    cdef public object combat_time
    cdef public object cube_advanced
    cdef public object cur_mode
    cdef public object cur_round
    cdef public object custom_health_multiplier
    cdef public object deferred_flush_enabled
    cdef public object eb_relay_mirrored
    cdef public object event_type_keys
    cdef public object fatigueDamageSource
    cdef public object fight_ended
    cdef public object flk_delay_cursor
    cdef public object frame_counter
    cdef public object hooks
    cdef public object item_book
    cdef public object keyed_cleanse_biggest_first
    cdef public object keyed_stop_clears_seen
    cdef public object label_rng_enabled
    cdef public object lib_fires
    cdef public object lobbies_mode
    cdef public object opponent
    cdef public object out_of_stamina_count
    cdef public object player
    cdef public object probe_pass
    cdef public object rng
    cdef public object rope_speedups
    cdef public object sandbag_active
    cdef public object stealLifeDamageSource
    cdef public object time
    cdef public object unhealingDamageSource
    cdef public object util
    cdef public object warn_unknown_api

