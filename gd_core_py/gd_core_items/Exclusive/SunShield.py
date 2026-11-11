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
if "_base_cls_Exclusive__SunShield" not in globals():
	from ..Shield import Shield_2 as _base_cls_Exclusive__SunShield





class Exclusive__SunShield(_base_cls_Exclusive__SunShield):

	resource_path = "res://gd_core_items/Exclusive/SunShield.gd"

	def _init_fields(self):
		super()._init_fields()
		self._blockAcc = 0
		self._bonusDamagePerTick = 0
		self._damagePerTick = 0
		self._blockPerTick = 0
		self.activationParticles = None

	@property
	def blockAcc(self):
		return self._blockAcc
	@blockAcc.setter
	def blockAcc(self, v):
		self._blockAcc = int(v)
	@property
	def bonusDamagePerTick(self):
		return self._bonusDamagePerTick
	@bonusDamagePerTick.setter
	def bonusDamagePerTick(self, v):
		self._bonusDamagePerTick = int(v)
	@property
	def damagePerTick(self):
		return self._damagePerTick
	@damagePerTick.setter
	def damagePerTick(self, v):
		self._damagePerTick = int(v)
	@property
	def blockPerTick(self):
		return self._blockPerTick
	@blockPerTick.setter
	def blockPerTick(self, v):
		self._blockPerTick = int(v)

	def canAffect(self, item):
		return item.canBlock()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "gave_block", "onItemGaveBlock")
		self.bonusDamagePerTick = 0


	def afterBlock(self):
		self.drainStamina(self.getP2(), self.blockedDamageRes.event)
		self.activate()


	def onItemGaveBlock(self, amount, event):
		self.blockAcc += amount
		ticks = _div(self.blockAcc, self.blockPerTick)
		if ticks > 0:
			self.blockAcc %= self.blockPerTick
			dam = ticks * (self.damagePerTick + self.bonusDamagePerTick)
			damageRes = self.dealEffectDamage(dam, event)
			self.miniActivate()




	def canBlockDamageRes(self, damageRes):
		return damageRes.triggerOnAttacked()


	def addBonusDamageOnTick(self, dam):
		self.bonusDamagePerTick += dam

	def _readyInit(self):
		super()._readyInit()
		self.damagePerTick = self.getP4()
		self.blockPerTick = self.getP3()
		self.damageSource = _H_1().setItem(self)
		self.damageSource.unsetFlag(_H_2)



_R.reg("res://gd_core_items/Exclusive/SunShield.gd", Exclusive__SunShield)
_R.reg("SunShield", Exclusive__SunShield)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")
try:
	_H_2 = _R.C("CoreDamageSource").Flags.CanCrit
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
