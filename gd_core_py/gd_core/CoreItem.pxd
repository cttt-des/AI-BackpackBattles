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
    cdef public bint _cooldown_active
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
    cdef public double baseCooldownOverride
    cdef public double bonusAccuracy
    cdef public double bonusChancePercent_additive1
    cdef public double bonusChancePercent_additive2
    cdef public double bonusChancePercent_mult
    cdef public double bonusDamageFactor
    cdef public double bonusMaxDam
    cdef public double bonusMinDam
    cdef public object buffAmplificationChances
    cdef public object buffLabelPositionTimestamps
    cdef public object buffPowers
    cdef public object cachedAffectedItems
    cdef public object chanceRng
    cdef public object character_
    cdef public object chargeFrame
    cdef public object collisionCells
    cdef public object combatConnections
    cdef public bint consumed
    cdef public double critChancePercent
    cdef public double critSeverity
    cdef public object ctx
    cdef public object currentAffectedItems
    cdef public object damageRangeRng
    cdef public object damageSource
    cdef public object descriptor
    cdef public double doubleActivationChance
    cdef public double doubleAttackEffectChance
    cdef public bint dragged
    cdef public object dynamicTypes
    cdef public object extensionCells
    cdef public bint flk_suppress_fire
    cdef public object gems
    cdef public bint hasDealtDamageEffect
    cdef public bint hasOnChargeLeftEffect
    cdef public bint hasOnChargeReceivedEffect
    cdef public bint hasPreDealDamageEarlyEffect
    cdef public bint hasPreDealDamageLateEffect
    cdef public object inventory
    cdef public object itemMetrics
    cdef public double iterationCooldown
    cdef public double lastActivationTime
    cdef public double lastTriggerTime
    cdef public object name
    cdef public object occupiedCells
    cdef public object paramAdd
    cdef public object paramMult
    cdef public bint placed
    cdef public bint placedByPlayer
    cdef public double removableDam
    cdef public bint replacementPending
    cdef public double rotation
    cdef public double speedScale
    cdef public double staminaFactor
    cdef public object statDisplayOverrides
    cdef public object timers
    cdef public double triggerTime
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
    cpdef double getSpeed(self)
    cpdef double speed(self)
    cpdef double getStackSpeedMods(self)
    cpdef bint isCooldownActive(self)
    cpdef double getBaseCooldown(self)
    cpdef double getBaseCooldownIndex(self, long long index)
    cpdef double getCooldown(self)
    cpdef double getCooldownIndex(self, long long index)
    cpdef double getModifiedCooldown(self)
    cpdef double getBaseStaminaCost(self)
    # cpdef double getStaminaCost(self)  # ← §8.3 事故回退（2026-11-13 晚）：
    #   cpdef double + plain 子类(Greatsword_2) def 覆写 + 零参 super() 三元组合
    #   在 Cython 3.3.1 下 62 场崩（super(): __class__ cell not found，纯 py 臂
    #   1/1 全绿——纯编译层回归）。与 binding=False 事故同指纹；binding=True
    #   不救（实证 2026-11-13 晚，双臂+重编复现）。退 plain def 动态派发。
    #   §11.7 闭环已判 1.07-1.10x 不划算，此处让收益换正确性。
    cpdef long long isStaminaModified(self)
    cpdef bint hasStartofBattle(self)
    cpdef bint checkTriggerCount(self, long long limit)
    cpdef bint checkActivationLimit(self)
    cpdef long long getBaseMinDamage(self)
    cpdef long long getBaseMaxDamage(self)
    cpdef double getBaseAverageDamage(self)
    cpdef double getAverageDamage(self)
    cpdef double getRemovableDamage(self)
    cpdef double getBaseChance(self)
    cpdef double getBaseChance2(self)
    cpdef double getChance(self)
    cpdef double getChance2(self)
    cpdef bint rollChance2(self)
    cpdef long long getCritTokens(self)
    cpdef double getCritSeverity(self)
    cpdef long long rollDoubleAttackEffect(self)
    cpdef double getBaseAccuracy(self)
    cpdef double getAccuracy(self)
    cpdef long long getBlock(self)
    cpdef long long getIndex(self)
    cpdef long long getRarity(self)
    cpdef double getShopChance(self)
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
    cpdef double getP1(self)
    cpdef double getP2(self)
    cpdef double getP3(self)
    cpdef double getP4(self)
    cpdef double getP5(self)
    cpdef double getP6(self)
    cpdef double getP7(self)
    cpdef double getP8(self)
    cpdef double getP9(self)
    cpdef double getP10(self)
    cpdef double getDPS(self)
    cpdef long long isDPSModified(self)
    cpdef long long isCooldownModified(self)
    cpdef long long isAccuracyModified(self)
    cpdef long long isChance1Modified(self)
    cpdef long long isChance2Modified(self)
    cpdef long long isDamageModified(self)
    cpdef double getBaseStaminaPerSecond(self)
    cpdef double getStaminaPerSecond(self)
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

