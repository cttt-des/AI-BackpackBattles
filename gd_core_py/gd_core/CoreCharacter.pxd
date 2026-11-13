# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

from gd_core_py._rt cimport GodotObject


cdef class CoreCharacter(GodotObject):

    cdef public object INVENTORY
    cdef public bint _autoRage_active
    cdef public double _autoRage_left
    cdef public object _bonusFatigueDamage
    cdef public object _buffProtectStacks
    cdef public object _characterClass
    cdef public object _critResistStacks
    cdef public object _critTokens
    cdef public object _damageReduction
    cdef public object _debuffReflectStacks
    cdef public object _debuffResistStacks
    cdef public object _dodgeStacks
    cdef public bint _invul_active
    cdef public double _invul_eng
    cdef public double _invul_left
    cdef public double _invul_seen
    cdef public object _playerId
    cdef public bint _rage_active
    cdef public double _rage_eng
    cdef public double _rage_left
    cdef public double _rage_seen
    cdef public bint _tick_timer_active
    cdef public double _tick_timer_left
    cdef public object accuracyRng
    cdef public bint allowStaminaOverflow
    cdef public bint attack_moving_forward
    cdef public object attack_sound_ready_time
    cdef public object autoRageItem
    cdef public double baseMaxStamina
    cdef public double baseStaminaRegen
    cdef public object battleRageAura
    cdef public double battleRageBonusDur
    cdef public bint blindingLightActive
    cdef public object buffs
    cdef public object character_died_handlers
    cdef public bint chibi
    cdef public double critResistance
    cdef public object critResistanceRng
    cdef public object critRng
    cdef public long long critTokensUsed
    cdef public object ctx
    cdef public double curHealth
    cdef public double curStamina
    cdef public double damageResistance
    cdef public object damage_anim_current
    cdef public double effectSpikesLimit
    cdef public double empowerDamage
    cdef public double healingEfficiency
    cdef public object inventory
    cdef public object invulnerabilityItem
    cdef public bint invulnerable
    cdef public bint isDead
    cdef public object items
    cdef public double maxHealth
    cdef public double maxStamina
    cdef public double meleeSpikesLimit
    cdef public double meleeVampirismLimit
    cdef public object opponent
    cdef public object poisonDamageSource
    cdef public double rangedSpikesLimit
    cdef public double rangedVampirismLimit
    cdef public object spikeDamageSource
    cdef public double staminaRegen
    cdef public bint staminaUpdateQueued
    cdef public object statsDisplay
    cdef public double stunResistance
    cdef public object stunResistanceRng
    cdef public double stunnedDuration
    cdef public double temporaryMaxHealth
    cdef public double temporaryMaxHealthGain
    cdef public double temporaryMaxStamina
    cdef public long long tickCounter
    cdef public object typedDamageFactors
    cdef public double unhealingAmount
    cpdef bint isPlayer(self)
    cpdef long long getMissingHealth(self)
    cpdef double getBaseMaxHealth(self)
    cpdef double getMaxHealth(self)
    cpdef double getMaxStamina(self)
    cpdef bint isStunned(self)
    cpdef bint critResisted(self)
    cpdef bint stunResisted(self)
    cpdef double getUnhealing(self)
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
    cpdef double getBuffDamageMod(self)
    cpdef double getBaseMaxStamina(self)
    cpdef double getMaxBaseStamina(self)
    cpdef double getCurrentStamina(self)
    cpdef double getMissingStamina(self)
    cpdef bint isFullStamina(self)

