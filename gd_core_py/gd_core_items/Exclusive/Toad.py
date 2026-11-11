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
if "_base_cls_Exclusive__Toad" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Toad





class Exclusive__Toad(_base_cls_Exclusive__Toad):

	resource_path = "res://gd_core_items/Exclusive/Toad.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItemsDict = {}
		self._gainedBuffs = 0
		self._usedBuffs = 0
		self.gainedThreshold = None
		self.usedThreshold = None
		self.luck = None
		self.mana = None
		self.luck2 = None
		self.mana2 = None

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

	def canAffect(self, item):
		return item.gainsBuffs() or item.usesBuffs()


	def onPrepare(self):
		self.affectedItemsDict = self.ctx.util.arrayAsIndexDict(self.getAffectedItems())
		self.connectToCharacterBuffs("onBuffsChanged")
		self.gainedBuffs = 0
		self.usedBuffs = 0


	def onGainThresholdReached(self, ticks, event):
		self.heal(ticks * self.getP_m("heal"), event)
		self.miniActivate()


	def onUseThresholdReached(self, ticks, event):
		self.giveLucky(ticks * self.luck, event)
		self.giveMana(ticks * self.mana, event)
		self.miniActivate()


	def onBuffsChanged(self, amount, event):
		_div__loc = _div
		if event.getOrigin() in self.affectedItemsDict:
			if amount > 0:
				self.gainedBuffs += amount
				ticks = _div__loc(self.gainedBuffs, self.gainedThreshold)
				if ticks > 0:
					self.onGainThresholdReached(ticks, event)
					self.gainedBuffs %= self.gainedThreshold
			else:

				self.usedBuffs += int(abs(amount))
				ticks = _div__loc(self.usedBuffs, self.usedThreshold)
				if ticks > 0:
					self.onUseThresholdReached(ticks, event)
					self.usedBuffs %= self.usedThreshold


	def doCooldownEffect(self):
		self.giveLucky(self.luck2)
		self.giveMana(self.mana2)
		self.activate()


	def playPickupSound(self):
		# decomp Items/Exclusive/Toad.gd:57 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Toad.gd:61 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.gainedThreshold = int(self.getP("gained"))
		self.usedThreshold = int(self.getP("used"))
		self.luck = int(self.getP("luck"))
		self.mana = int(self.getP("mana"))
		self.luck2 = int(self.getP("luck2"))
		self.mana2 = int(self.getP("mana2"))


_R.reg("res://gd_core_items/Exclusive/Toad.gd", Exclusive__Toad)
_R.reg("Toad", Exclusive__Toad)
