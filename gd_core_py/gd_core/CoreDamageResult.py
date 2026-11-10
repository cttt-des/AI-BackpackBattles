# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R




class CoreDamageResult(GodotObject):

	resource_path = "res://gd_core/CoreDamageResult.gd"

	def _init_fields(self):
		super()._init_fields()
		self.event = None
		self.damageSource = None
		self._damage = 0
		self._healthDamage = 0
		self.hit = False
		self.critical = False
		self._damageReduction = 0
		self._ctx = None

	@property
	def damage(self):
		return self._damage
	@damage.setter
	def damage(self, v):
		self._damage = int(v)
	@property
	def healthDamage(self):
		return self._healthDamage
	@healthDamage.setter
	def healthDamage(self, v):
		self._healthDamage = int(v)
	@property
	def damageReduction(self):
		return self._damageReduction
	@damageReduction.setter
	def damageReduction(self, v):
		self._damageReduction = int(v)
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
		if isinstance(self.damageSource.origin, _H_1):
			self.damage *= self.damageSource.origin.getCritSeverity()
		else:
			self.damage *= _H_2
		self.critical = True


	def applyDamageReduction(self, amount, item):
		leftOverDmg = max(0, self.damage - self.damageReduction)
		actualReduction = min(amount, leftOverDmg)
		item.addMetric(_H_3, actualReduction)

		self.damageReduction += amount


	def triggerOnHit(self):
		return self.hasHit() and self.canTriggerItems()


	def triggerOnDamaged(self):
		return self.getDamage() > 0 and self.canTriggerItems()


	def triggerOnMeleeAttacked(self):
		return (self.hasHit() and 
				self.canTriggerItems() and 
				self.damageSource.hasType(_H_5))


	def triggerOnAttacked(self):
		return (self.hasHit() and 
				self.canTriggerItems() and 
				self.damageSource.isAttack())


	def canTriggerItems(self):
		return self.damageSource.flags & _H_4


	def canTriggerSpikes(self):
		return self.hasHit() and self.getDamage() > 0 and self.damageSource.canTriggerSpikes()


	def canTriggerVampirism(self):
		return self.hasHit() and self.getDamage() > 0 and self.damageSource.canTriggerVampirism()


	def willBeLethal(self, character):
		return self.damage >= (character.getCurrentHealth() + character.getBlock())


_R.reg("res://gd_core/CoreDamageResult.gd", CoreDamageResult)
_R.reg("CoreDamageResult", CoreDamageResult)
_R.reg("CoreDamageResult", CoreDamageResult)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreItem")
try:
	_H_2 = _R.C("CoreItem").BASE_CRIT_SEVERITY
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").ItemMetrics.DamageBlocked
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
try:
	_H_4 = _R.C("CoreDamageSource").Flags.CanTriggerItems
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
try:
	_H_5 = _R.C("CoreDamageSource").Type.Melee
except AttributeError as _he:
	_H_5 = _HoistPending(_he)
