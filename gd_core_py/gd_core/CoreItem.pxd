# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py（M1-2/L1 实例槽位声明）
#
# 仅收录本模块「可 cdef」的类（基类链全 cdef）；keep-plain 类（运行时
# 基类/辅助形态）不在此声明，.py 里保持 plain class——同模块混布合法。
# 槽位 object 型起步；引擎补充槽见 tools/gd_to_py.py _PXD_EXTRA_SLOTS。

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
    cpdef bint hasCharacter(self)
    cpdef bint isPlaced(self)
    cpdef bint isCoreItem(self)
    cpdef bint isPlayer(self)
    cpdef long long getTypeMultiplicity(self, long long type)
    cpdef bint isWeapon(self)
    cpdef bint isBattleRageItem(self)
    cpdef bint canDamage(self)
    cpdef bint canBeEmpowered(self)
    cpdef bint canActivate(self)
    cpdef bint isCooldownActive(self)
    cpdef long long isStaminaModified(self)
    cpdef bint hasStartofBattle(self)
    cpdef bint checkTriggerCount(self, long long limit)
    cpdef bint checkActivationLimit(self)
    cpdef long long getBaseMinDamage(self)
    cpdef long long getBaseMaxDamage(self)
    cpdef bint rollChance2(self)
    cpdef long long getCritTokens(self)
    cpdef long long rollDoubleAttackEffect(self)
    cpdef long long getBlock(self)
    cpdef long long getIndex(self)
    cpdef long long getRarity(self)
    cpdef long long getMainType(self)
    cpdef long long getNumStaticTypes(self)
    cpdef bint isNeutral(self)
    cpdef bint isTreasure(self)
    cpdef bint isSubclassItem(self)
    cpdef bint isOwnable(self)
    cpdef bint isOwnedByOpponent(self)
    cpdef bint isGateItem(self)
    cpdef bint isShowCaseItem(self)
    cpdef bint hasOpponent(self)
    cpdef long long getEffectiveOwnerType(self)
    cpdef bint isBusy(self)
    cpdef bint isBoundAsIngredient(self)
    cpdef long long isDPSModified(self)
    cpdef long long isCooldownModified(self)
    cpdef long long isAccuracyModified(self)
    cpdef long long isChance1Modified(self)
    cpdef long long isChance2Modified(self)
    cpdef long long isDamageModified(self)
    cpdef long long isStaminaPerSecondModified(self)
    cpdef bint canHealOrLifesteal(self)
    cpdef bint canModifyChance(self)
    cpdef bint canUseStamina(self)
    cpdef bint hasAttackEffect(self)
    cpdef bint gainsBuffs(self)
    cpdef bint usesBuffs(self)
    cpdef bint inflictsDebuffs(self)
    cpdef bint reactsToCharges(self)
    cpdef bint hasSockets(self)
    cpdef long long getNumSockets(self)
    cpdef bint hasGems(self)
    cpdef bint canCombine(self)
    cpdef long long getAffectedGoldValue(self)
    cpdef bint hasSameOrientationAsPickup(self)

