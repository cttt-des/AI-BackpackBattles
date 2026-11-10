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


cdef class CoreCharacter(GodotObject):

    cdef public object INVENTORY
    cdef public object _autoRage_active
    cdef public object _autoRage_left
    cdef public object _bonusFatigueDamage
    cdef public object _buffProtectStacks
    cdef public object _characterClass
    cdef public object _critResistStacks
    cdef public object _critTokens
    cdef public object _damageReduction
    cdef public object _debuffReflectStacks
    cdef public object _debuffResistStacks
    cdef public object _dodgeStacks
    cdef public object _invul_active
    cdef public object _invul_eng
    cdef public object _invul_left
    cdef public object _invul_seen
    cdef public object _playerId
    cdef public object _rage_active
    cdef public object _rage_eng
    cdef public object _rage_left
    cdef public object _rage_seen
    cdef public object _tick_timer_active
    cdef public object _tick_timer_left
    cdef public object accuracyRng
    cdef public object allowStaminaOverflow
    cdef public object attack_moving_forward
    cdef public object attack_sound_ready_time
    cdef public object autoRageItem
    cdef public object baseMaxStamina
    cdef public object baseStaminaRegen
    cdef public object battleRageAura
    cdef public object battleRageBonusDur
    cdef public object blindingLightActive
    cdef public object buffs
    cdef public object character_died_handlers
    cdef public object chibi
    cdef public object critResistance
    cdef public object critResistanceRng
    cdef public object critRng
    cdef public object critTokensUsed
    cdef public object ctx
    cdef public object curHealth
    cdef public object curStamina
    cdef public object damageResistance
    cdef public object damage_anim_current
    cdef public object effectSpikesLimit
    cdef public object empowerDamage
    cdef public object healingEfficiency
    cdef public object inventory
    cdef public object invulnerabilityItem
    cdef public object invulnerable
    cdef public object isDead
    cdef public object items
    cdef public object maxHealth
    cdef public object maxStamina
    cdef public object meleeSpikesLimit
    cdef public object meleeVampirismLimit
    cdef public object opponent
    cdef public object poisonDamageSource
    cdef public object rangedSpikesLimit
    cdef public object rangedVampirismLimit
    cdef public object spikeDamageSource
    cdef public object staminaRegen
    cdef public object staminaUpdateQueued
    cdef public object statsDisplay
    cdef public object stunResistance
    cdef public object stunResistanceRng
    cdef public object stunnedDuration
    cdef public object temporaryMaxHealth
    cdef public object temporaryMaxHealthGain
    cdef public object temporaryMaxStamina
    cdef public object tickCounter
    cdef public object typedDamageFactors
    cdef public object unhealingAmount

