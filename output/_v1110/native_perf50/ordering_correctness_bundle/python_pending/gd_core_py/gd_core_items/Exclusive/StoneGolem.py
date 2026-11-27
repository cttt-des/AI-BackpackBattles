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
    _has_behavior_cache_get,
    _has_behavior_cache_put,
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
if "_base_cls_Exclusive__StoneGolem" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__StoneGolem





class Exclusive__StoneGolem(_base_cls_Exclusive__StoneGolem):

	resource_path = "res://gd_core_items/Exclusive/StoneGolem.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.hasStunned = False
		self.empower = None
		self.regenThreshold = None
		self.bagOfStonesDescriptor = None
		self.activationParticles1 = None
		self.activationParticles2 = None


	def canAffect(self, item):
		return item.isA(self.bagOfStonesDescriptor)


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_regeneration_changed", "onRegenChanged")
		self.setState(False)


	def onPreCombatStart(self):
		self.addBonusDamage(self.getP("bonusdam") * self.getNumAffectedItems())


	def onRegenChanged(self, amount, event):
		if not self.activated and amount > 0:
			if self.character().getRegeneration() >= self.regenThreshold:
				self.setState(True, True)
				event2 = self.useRegeneration(self.regenThreshold, event)
				self.giveBlock(self.getBlock(), True, event2)
				self.baseCooldownOverride = self.getP4()
				self.updateBaseCooldown()


	def attack(self, triggerEvent=None):
		self.hasStunned = False
		res = self.dealDamage(triggerEvent)
		if self.hasStunned:
			self.activate(res, True, False, self.ActivationAni.Tackle)
		else:
			self.activate(res)


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.giveEmpower(self.empower)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			if self.rollChance():
				self.hasStunned = True
				self.stun(self.getP_m("dur_stun"), damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, active):
		if active:
			pass
		else:
			pass

		self.activated = active


	def getTriggerPriority(self):
		return _H_1 + 1

	def _readyInit(self):
		super()._readyInit()
		self.empower = self.getP("empower")
		self.regenThreshold = self.getP("regen")
		self.bagOfStonesDescriptor = self.ctx.item_book.getDescriptor("Bag of Stones")


_R.reg("res://gd_core_items/Exclusive/StoneGolem.gd", Exclusive__StoneGolem)
_R.reg("StoneGolem", Exclusive__StoneGolem)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
