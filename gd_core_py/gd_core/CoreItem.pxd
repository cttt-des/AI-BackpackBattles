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


cdef class CoreElectricalCharge(GodotObject):

    cdef public object curChargedItem
    cdef public object lastChargedItem


from gd_core_py._rt cimport GodotObject


cdef class CoreSignalConnection(GodotObject):

    cdef public object emitter
    cdef public object methodName
    cdef public object receiver
    cdef public object signalName


from gd_core_py._rt cimport GodotObject


cdef class CoreItem(GodotObject):

    cdef public object __inj_trigger_count
    cdef public object __inj_trigger_n
    cdef public object _activationsThisFrame
    cdef public object _behavior
    cdef public object _cooldown_active
    cdef public object _critTokens
    cdef public object _faceDirection
    cdef public object _grid
    cdef public object _inj_item
    cdef public object _numCharges
    cdef public object _ownerType
    cdef public object _triggersThisFrame
    cdef public object affectedCellsCache
    cdef public object affectedExtensionCells
    cdef public object affectedTileCells
    cdef public object baseCooldownOverride
    cdef public object bonusAccuracy
    cdef public object bonusChancePercent_additive1
    cdef public object bonusChancePercent_additive2
    cdef public object bonusChancePercent_mult
    cdef public object bonusDamageFactor
    cdef public object bonusMaxDam
    cdef public object bonusMinDam
    cdef public object buffAmplificationChances
    cdef public object buffLabelPositionTimestamps
    cdef public object buffPowers
    cdef public object cachedAffectedItems
    cdef public object chanceRng
    cdef public object character_
    cdef public object chargeFrame
    cdef public object collisionCells
    cdef public object combatConnections
    cdef public object consumed
    cdef public object critChancePercent
    cdef public object critSeverity
    cdef public object ctx
    cdef public object currentAffectedItems
    cdef public object damageRangeRng
    cdef public object damageSource
    cdef public object descriptor
    cdef public object doubleActivationChance
    cdef public object doubleAttackEffectChance
    cdef public object dragged
    cdef public object dynamicTypes
    cdef public object extensionCells
    cdef public object flk_suppress_fire
    cdef public object gems
    cdef public object hasDealtDamageEffect
    cdef public object hasOnChargeLeftEffect
    cdef public object hasOnChargeReceivedEffect
    cdef public object hasPreDealDamageEarlyEffect
    cdef public object hasPreDealDamageLateEffect
    cdef public object inventory
    cdef public object itemMetrics
    cdef public object iterationCooldown
    cdef public object lastActivationTime
    cdef public object lastTriggerTime
    cdef public object name
    cdef public object occupiedCells
    cdef public object paramAdd
    cdef public object paramMult
    cdef public object placed
    cdef public object placedByPlayer
    cdef public object removableDam
    cdef public object replacementPending
    cdef public object rotation
    cdef public object speedScale
    cdef public object staminaFactor
    cdef public object statDisplayOverrides
    cdef public object timers
    cdef public object triggerTime

