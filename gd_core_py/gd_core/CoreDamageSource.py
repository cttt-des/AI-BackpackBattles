# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreDamageSource(GodotObject):

	resource_path = "res://gd_core/CoreDamageSource.gd"

	Type = EnumDict("Type", {"Melee": 0, "Ranged": 1, "Effect": 2, "SelfDamage": 3, "Unhealing": 98, "Spikes": 104, "Poison": 108, "Fatigue": 99})

	Flags = EnumDict("Flags", {"None": 0, "CanBeBlocked": 1, "CanTriggerSpikes": 2, "CanTriggerVampirism": 4, "CanTriggerItems": 8, "CanMiss": 16, "CanCrit": 32, "All": 63})



	def _init_fields(self):
		super()._init_fields()
		self.minDamage = 0
		self.maxDamage = 0
		self.types = []
		self.accuracy = 100
		self.critChancePercent = 0
		self.origin = None
		self.flags = self.Flags.All
		self._rng = None

	# =============================================================================
	# CoreDamageSource.gd — 无头战斗内核：伤害源
	# =============================================================================
	# 对齐源码：Utility/DamageSource.gd（全文 171 行）
	#
	# 剥离内容：
	#   · `Util.rng.randi_range(...)` → 注入的 CoreRng（同一套语义，仅换随机源持有者）
	#   · `origin is Item` → `origin is CoreItem`（类型改名，判定不变）
	#   · `item.hasType(Item.Type.X)` → `item.hasType(CoreConst.Type.X)`
	#     （原版 Item.gd:34-67 的 Type 枚举已整体收拢到 CoreConst.Type，取值逐项相同，
	#       hasType 只按整数值判成员，判定不变）
	#   · 无其他改动；枚举值、flags 常量、函数体逐字保留。
	# =============================================================================



	damTypeNames = {
		Type.Melee: "melee", 
		Type.Ranged: "ranged", 
		Type.Effect: "effect"
	}



	chipDamageFlags = Flags.CanBeBlocked
	meleeFlags = Flags.All
	rangedFlags = Flags.All
	effectFlags = Flags.CanBeBlocked + Flags.CanTriggerItems + Flags.CanCrit
	unhealingFlags = Flags.CanBeBlocked + Flags.CanTriggerItems
	selfDamageFlags = Flags.CanBeBlocked + Flags.CanTriggerItems



	def fromDamageSource(self, otherDamSource):
		self.minDamage = otherDamSource.minDamage
		self.maxDamage = otherDamSource.maxDamage
		self.types = _dup(otherDamSource.types)
		self.accuracy = otherDamSource.accuracy
		self.critChancePercent = otherDamSource.critChancePercent
		self.flags = otherDamSource.flags
		self.origin = otherDamSource.origin
		return self


	def setItem(self, item, _type=None):
		if _type != None:
			self.types = [_type]
		else:
			if item.hasType(_R.C("CoreConst").Type.Ranged):
				self.types.append(self.Type.Ranged)

			if item.hasType(_R.C("CoreConst").Type.Melee):
				self.types.append(self.Type.Melee)

			if item.hasType(_R.C("CoreConst").Type.Effect):
				self.types.append(self.Type.Effect)

			if (not self.types):
				self.types.append(self.Type.Effect)

		if self.hasType(self.Type.Melee):
			self.flags = self.meleeFlags
		elif self.hasType(self.Type.Ranged):
			self.flags = self.rangedFlags
		elif self.hasType(self.Type.SelfDamage):
			self.flags = self.selfDamageFlags
		else:
			self.flags = self.effectFlags

		return self.init(item, self.types, item.getMinDamage(), item.getMaxDamage(), item.getAccuracy())


	def init(self, _origin=None, _type=GD_DEFAULT, _minDamage=0, _maxDamage=None, _accuracy=100):
		if _type is GD_DEFAULT:
			_type = self.Type.Effect

		self.origin = _origin
		if isinstance(_type, list):
			self.types = _type
		else:
			self.types = [_type]
		self.setDamage(_minDamage, _maxDamage)
		self.accuracy = _accuracy
		return self


	def hasType(self, _type):
		return _type in self.types


	def setDamage(self, _minDamage, _maxDamage=None):
		self.minDamage = _minDamage
		if _maxDamage:
			self.maxDamage = _maxDamage
		else:
			self.maxDamage = self.minDamage


	def addDamage(self, _damage):
		self.minDamage += _damage
		self.maxDamage += _damage


	def getCritChancePercent(self):
		return clamp(self.critChancePercent, 0.0, 100.0)


	def updateItem(self, item):
		self.accuracy = item.getAccuracy()


	def updateEffect(self, item, damage):
		self.origin = item
		self.setDamage(item.getModifiedEffectDamage(damage))
		self.critChancePercent = item.getCritChancePercent()


	def addCritChancePercent(self, _critChance):
		self.critChancePercent += _critChance


	def setFlag(self, flag):
		self.flags |= flag


	def unsetFlag(self, flag):
		self.flags = self.flags & ~ flag


	def canMiss(self):
		return self.flags & self.Flags.CanMiss


	def canTriggerSpikes(self):
		return self.flags & self.Flags.CanTriggerSpikes


	def canTriggerVampirism(self):
		return self.flags & self.Flags.CanTriggerVampirism


	def canBeBlocked(self):
		return self.flags & self.Flags.CanBeBlocked


	def canCrit(self):
		return self.flags & self.Flags.CanCrit


	def isAttack(self):
		return self.hasType(self.Type.Melee) or self.hasType(self.Type.Ranged)


	def isEffectDamage(self):
		return self.hasType(self.Type.Effect) or self.hasType(self.Type.Unhealing)


	def isAttackOrEffect(self):
		return self.isAttack() or self.isEffectDamage()


	def canApplyLifesteal(self):
		return self.isAttack() or self.hasType(self.Type.Effect)


	def makeSpectral(self):
		self.unsetFlag(self.Flags.CanBeBlocked)


	# ── 唯一改动点：随机源注入（原为 Util.rng） ──


	def randDamage(self):
		# 原版 `origin is Item`；此处改用类型标记 isCoreItem()（鸭子类型），
		# 因为 CoreDamageSource ↔ CoreItem 的 class_name 互相引用会构成
		# GDScript 3 禁止的循环依赖。判定语义完全一致（CoreItem 恒返回 true）。
		if self.origin != None and self.origin.has_method("isCoreItem"):
			self.critChancePercent = self.origin.getCritChancePercent()
			if self.isAttack():
				self.setDamage(self.origin.getMinDamage(self), self.origin.getMaxDamage(self))
			return self.origin.damageRangeRng.randIntRange(self.minDamage, self.maxDamage)
		else:
			return self._rng.randi_range(self.minDamage, self.maxDamage)


_R.reg("res://gd_core/CoreDamageSource.gd", CoreDamageSource)
_R.reg("CoreDamageSource", CoreDamageSource)
_R.reg("CoreDamageSource", CoreDamageSource)
