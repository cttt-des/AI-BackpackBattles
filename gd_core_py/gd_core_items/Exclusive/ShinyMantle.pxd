# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py.gd_core_items.Item cimport Item_2 as _base_cls_Exclusive__ShinyMantle


cdef class Exclusive__ShinyMantle(_base_cls_Exclusive__ShinyMantle):

    cdef public object _invuProcced
    cdef public object activationParticles
    cdef public object blind
    cdef public object buffTimer
    cdef public object gemDurFactor
    cdef public object manaCostIncrease
    cdef public object manaNeeded
    cdef public object manaNeeded_base
    cdef public object maxUses

