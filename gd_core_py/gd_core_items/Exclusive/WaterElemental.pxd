# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py.gd_core_items.Weapon cimport Weapon_2 as _base_cls_Exclusive__WaterElemental


cdef class Exclusive__WaterElemental(_base_cls_Exclusive__WaterElemental):

    cdef public object _manaUsed
    cdef public object activeEffects
    cdef public object bonusDam
    cdef public object bonusManaOnHit
    cdef public object coldOnHit
    cdef public object coldParticles
    cdef public object distortion
    cdef public object iceSpeed
    cdef public object manaNeeded1
    cdef public object manaNeeded2
    cdef public object manaNeeded3
    cdef public object manaOnHit

