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
if "_base_cls_Exclusive__Phoenix" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Phoenix





class Exclusive__Phoenix(_base_cls_Exclusive__Phoenix):

	resource_path = "res://gd_core_items/Exclusive/Phoenix.gd"

	def _init_fields(self):
		super()._init_fields()
		self.ashSprite = None
		self.deathPrevented = False
		self.normalSprite = None
		self._selfDam = 0
		self._reincarnateHealth = 0

	@property
	def selfDam(self):
		return self._selfDam
	@selfDam.setter
	def selfDam(self, v):
		self._selfDam = int(v)
	@property
	def reincarnateHealth(self):
		return self._reincarnateHealth
	@reincarnateHealth.setter
	def reincarnateHealth(self, v):
		self._reincarnateHealth = int(v)

	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_damaged", "onDamaged")


	def onDamaged(self, _damage, event):
		if self.deathPrevented:
			return

		if self.character().getCurrentHealth() <= 0:
			heat = self.character().getHeat()
			if heat > 0:
				self.setState(True)

				event2 = self.character().reincarnate(self.reincarnateHealth * heat, False, self, event)
				self.useHeat(heat, event2)
				self.activate()


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			if self.character().getCurrentHealth() > self.selfDam:
				self.character().loseHealth(self.selfDam, self)
				res = self.dealDamage()
				self.activate(res)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _deathPrevented):
		if _deathPrevented:
			pass
		else:
			pass
		self.deathPrevented = _deathPrevented

	def _readyInit(self):
		super()._readyInit()
		self.selfDam = self.getP("selfdam")
		self.reincarnateHealth = self.getP("reincarnate_health")


_R.reg("res://gd_core_items/Exclusive/Phoenix.gd", Exclusive__Phoenix)
_R.reg("Phoenix", Exclusive__Phoenix)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
