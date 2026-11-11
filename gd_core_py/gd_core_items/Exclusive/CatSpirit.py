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
if "_base_cls_Exclusive__CatSpirit" not in globals():
	from .SpiritCompanion import SpiritCompanion as _base_cls_Exclusive__CatSpirit





class Exclusive__CatSpirit(_base_cls_Exclusive__CatSpirit):

	resource_path = "res://gd_core_items/Exclusive/CatSpirit.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaNeeded = None
		self.luck = None
		self.empower = None


	def canAffect(self, item):
		return item.canDamage()


	def onPrepare(self):
		for item in _iter(self.getAffectedItems()):
			item.addCritChancePercent(self.getChance())


	def doCooldownEffect(self):
		if self.character().getMana() >= self.manaNeeded:
			event = self.useMana(self.manaNeeded)
			self.giveLucky(self.luck, event)
			self.giveEmpower(self.empower, event)

		self.activate()



	def playPickupSound(self):
		# decomp Items/Exclusive/CatSpirit.gd:27 Sound.playSound_process(pickupSound, - 12, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/CatSpirit.gd:31 Sound.playSound(dropSound, volume - 18, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP("manat"))
		self.luck = int(self.getP("luck"))
		self.empower = int(self.getP("empower"))


_R.reg("res://gd_core_items/Exclusive/CatSpirit.gd", Exclusive__CatSpirit)
_R.reg("CatSpirit", Exclusive__CatSpirit)
