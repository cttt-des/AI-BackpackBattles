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
if "_base_cls_Exclusive__PoisonFrog" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__PoisonFrog





class Exclusive__PoisonFrog(_base_cls_Exclusive__PoisonFrog):

	resource_path = "res://gd_core_items/Exclusive/PoisonFrog.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItemsDict = {}
		self._gainedBuffs = 0
		self._usedBuffs = 0
		self._gainedThreshold = 0
		self._usedThreshold = 0
		self.poison = None
		self.mana = None

	@property
	def gainedBuffs(self):
		return self._gainedBuffs
	@gainedBuffs.setter
	def gainedBuffs(self, v):
		self._gainedBuffs = int(v)
	@property
	def usedBuffs(self):
		return self._usedBuffs
	@usedBuffs.setter
	def usedBuffs(self, v):
		self._usedBuffs = int(v)
	@property
	def gainedThreshold(self):
		return self._gainedThreshold
	@gainedThreshold.setter
	def gainedThreshold(self, v):
		self._gainedThreshold = int(v)
	@property
	def usedThreshold(self):
		return self._usedThreshold
	@usedThreshold.setter
	def usedThreshold(self, v):
		self._usedThreshold = int(v)

	def canAffect(self, item):
		return item.gainsBuffs() or item.usesBuffs()


	def onPrepare(self):
		self.affectedItemsDict.clear()
		for item in _iter(self.getAffectedItems()):
			self.affectedItemsDict[item] = True
		self.connectToCharacterBuffs("onBuffsChanged")
		self.gainedBuffs = 0
		self.usedBuffs = 0


	def onBuffsChanged(self, amount, event):
		_div__loc = _div
		if event.getOrigin() in self.affectedItemsDict:
			if amount > 0:
				self.gainedBuffs += amount
				ticks = _div__loc(self.gainedBuffs, self.gainedThreshold)
				if ticks > 0:
					self.heal()


					self.gainedBuffs %= self.gainedThreshold
					self.miniActivate()

			else:

				self.usedBuffs += int(abs(amount))
				ticks = _div__loc(self.usedBuffs, self.usedThreshold)
				if ticks > 0:
					self.inflictPoison(ticks * self.poison, event)
					self.giveMana(ticks * self.mana, event)
					self.usedBuffs %= self.usedThreshold
					self.miniActivate()


	def doCooldownEffect(self):
		self.inflictPoison(self.getP("poison2"))
		self.giveMana(self.getP("mana2"))
		self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.gainedThreshold = self.getP("gained")
		self.usedThreshold = self.getP("used")
		self.poison = int(self.getP("poison"))
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/PoisonFrog.gd", Exclusive__PoisonFrog)
_R.reg("PoisonFrog", Exclusive__PoisonFrog)
