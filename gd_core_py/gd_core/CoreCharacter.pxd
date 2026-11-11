# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

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
    cpdef bint isPlayer(self)
    cpdef long long getMissingHealth(self)
    cpdef bint isStunned(self)
    cpdef bint critResisted(self)
    cpdef bint stunResisted(self)
    cpdef long long getCritTokens(self)
    cpdef long long getBonusFatigueDamage(self)
    cpdef long long getClass(self)
    cpdef bint isBattleRaging(self)
    cpdef long long getBuffStacks(self)
    cpdef long long getDebuffStacks(self)
    cpdef long long getBlock(self)
    cpdef long long getSpikes(self)
    cpdef long long getVampirism(self)
    cpdef long long getPoison(self)
    cpdef long long getRegeneration(self)
    cpdef long long getLucky(self)
    cpdef long long getBlind(self)
    cpdef long long getMana(self)
    cpdef long long getEmpower(self)
    cpdef long long getHeat(self)
    cpdef long long getCold(self)
    cpdef bint isFullStamina(self)

