# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreDamageResult(GodotObject):

	resource_path = "res://gd_core/CoreDamageResult.gd"

	def _init_fields(self):
		super()._init_fields()
		self.event = None
		self.damageSource = None
		self.damage = 0
		self.healthDamage = 0
		self.hit = False
		self.critical = False
		self.damageReduction = 0
		self._ctx = None

	# =============================================================================
	# CoreDamageResult.gd — 无头战斗内核：伤害结算载体
	# =============================================================================
	# 对齐源码：Utility/DamageResult.gd（全文 71 行）
	#
	# 剥离内容：
	#   · `damageSource.origin is Item` → `is CoreItem`
	#   · `Item.BASE_CRIT_SEVERITY` → `CoreItem.BASE_CRIT_SEVERITY`（同为 2.0）
	#   · `item.addMetric(...)` → `ctx.hooks.addMetric(...)`（统计埋点走空实现钩子）
	#   · 判定条件、取整、max/min 包裹一律逐字保留。
	# =============================================================================





	def reset(self):
		self.hit = False
		self.damage = 0
		self.healthDamage = 0
		self.critical = False
		self.event = None


	def getDamage(self):
		return self.damage


	def hasHit(self):
		return self.hit


	def wasCriticalHit(self):
		return self.hasHit() and self.critical


	def makeCritical(self):
		if isinstance(self.damageSource.origin, _R.C("CoreItem")):
			self.damage *= self.damageSource.origin.getCritSeverity()
		else:
			self.damage *= _R.C("CoreItem").BASE_CRIT_SEVERITY
		self.critical = True


	def applyDamageReduction(self, amount, item):
		leftOverDmg = max(0, self.damage - self.damageReduction)
		actualReduction = min(amount, leftOverDmg)
		item.addMetric(_R.C("CoreConst").ItemMetrics.DamageBlocked, actualReduction)

		self.damageReduction += amount


	def triggerOnHit(self):
		return self.hasHit() and self.canTriggerItems()


	def triggerOnDamaged(self):
		return self.getDamage() > 0 and self.canTriggerItems()


	def triggerOnMeleeAttacked(self):
		return (self.hasHit() and 
				self.canTriggerItems() and 
				self.damageSource.hasType(_R.C("CoreDamageSource").Type.Melee))


	def triggerOnAttacked(self):
		return (self.hasHit() and 
				self.canTriggerItems() and 
				self.damageSource.isAttack())


	def canTriggerItems(self):
		return self.damageSource.flags & _R.C("CoreDamageSource").Flags.CanTriggerItems


	def canTriggerSpikes(self):
		return self.hasHit() and self.getDamage() > 0 and self.damageSource.canTriggerSpikes()


	def canTriggerVampirism(self):
		return self.hasHit() and self.getDamage() > 0 and self.damageSource.canTriggerVampirism()


	def willBeLethal(self, character):
		return self.damage >= (character.getCurrentHealth() + character.getBlock())


_R.reg("res://gd_core/CoreDamageResult.gd", CoreDamageResult)
_R.reg("CoreDamageResult", CoreDamageResult)
_R.reg("CoreDamageResult", CoreDamageResult)
