# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

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
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__HeartShield" not in globals():
	from ..Shield import Shield_2 as _base_cls_Exclusive__HeartShield





class Exclusive__HeartShield(_base_cls_Exclusive__HeartShield):

	resource_path = "res://gd_core_items/Exclusive/HeartShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self._regenGiven = 0
		self.fillAnimation = None
		self.healamp = None
		self.blockFactor = None
		self.regenNeeded = None
		self.regenOnBlock = None
		self.regenMax = None

	@property
	def regenGiven(self):
		return self._regenGiven
	@regenGiven.setter
	def regenGiven(self, v):
		self._regenGiven = int(v)

	def canAffect(self, item):
		return (item.canBlock() or 
				item.canHealOrLifesteal() or 
				item.gainsStack(_H_1))


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.giveBuffPower(_H_2, self.blockFactor)
			item.changeHealAmp(self.healamp)
			item.changeAmplificiationChancePercent(_H_3, self.getChance2())

		self.setState(False)
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.regenGiven = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)

		if self.regenGiven < self.regenMax:
			self.giveRegeneration(self.regenOnBlock, self.blockedDamageRes.event)
			self.regenGiven += self.regenOnBlock
		self.activate()


	def onRegenChanged(self, amount, event):
		if amount > 0 and not self.activated and self.character().getRegeneration() >= self.regenNeeded:
			self.setState(True, True)
			event2 = self.useRegeneration(self.regenNeeded, event)
			self.giveMaxHealth(self.getP_m("maxhealth"), event2)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, filled):
		if self.activated == filled:
			return
		self.activated = filled

		if filled:
			pass
		else:
			pass



	def preTakeDamage(self, damageRes):
		if self.activated:
			if damageRes.damageSource.isAttackOrEffect() and self.rollChance():
				self.blockedDamageRes = damageRes
				self.beforeBlock()
		else:
			super().preTakeDamage(damageRes)

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.healamp = _div__loc(self.getP('healamp'), 100.0)
		self.blockFactor = _div__loc(self.getP('block'), 100.0)
		self.regenNeeded = int(self.getP("regent"))
		self.regenOnBlock = int(self.getP("regen"))
		self.regenMax = int(self.getP("max_regen"))


_R.reg("res://gd_core_items/Exclusive/HeartShield.gd", Exclusive__HeartShield)
_R.reg("HeartShield", Exclusive__HeartShield)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Stack.Regeneration
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").EventType.Block
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").EventType.Regeneration
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
