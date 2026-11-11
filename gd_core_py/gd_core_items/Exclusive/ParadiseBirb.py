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
if "_base_cls_Exclusive__ParadiseBirb" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ParadiseBirb





class Exclusive__ParadiseBirb(_base_cls_Exclusive__ParadiseBirb):

	resource_path = "res://gd_core_items/Exclusive/ParadiseBirb.gd"

	def _init_fields(self):
		super()._init_fields()
		self._numActivations = 0
		self.speedBonus = None
		self.maxActivations = None
		self.bonusHeal = None

	@property
	def numActivations(self):
		return self._numActivations
	@numActivations.setter
	def numActivations(self, v):
		self._numActivations = int(v)

	def canAffect(self, item):
		return (item.hasCooldown() or item.gainsBuffs() or item.canHealOrLifesteal())


	def onPrepare(self):
		self.numActivations = 0


	def doCooldownEffect(self):
		if self.numActivations < self.maxActivations:

			for item in _iter(self.getAffectedItems()):
				item.addSpeed(self.speedBonus)
				item.changeAmplificiationChancePercent_allBuffs(self.getChance())
				item.changeHealAmp(self.bonusHeal)

			self.numActivations += 1

			if self.numActivations == self.maxActivations:
				self.onAfterEffectFinished()
			else:
				self.activate()


	def playPickupSound(self):
		pitch = self.ctx.rng.randf_range(0.8, 1.0)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		pitch = self.ctx.rng.randf_range(0.8, 1.0)

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedBonus = _div__loc(self.getP('speed'), 100.0)
		self.maxActivations = int(self.getP("max"))
		self.bonusHeal = _div__loc(self.getP('healamp'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ParadiseBirb.gd", Exclusive__ParadiseBirb)
_R.reg("ParadiseBirb", Exclusive__ParadiseBirb)
