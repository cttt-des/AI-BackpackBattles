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
if "_base_cls_Exclusive__EvilHat" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__EvilHat





class Exclusive__EvilHat(_base_cls_Exclusive__EvilHat):

	resource_path = "res://gd_core_items/Exclusive/EvilHat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.selfBuffs = None
		self.opponentBuffs = None
		self.regen = None


	def canAffect(self, item):
		return item.canDamage()


	def canAffect_secondary(self, item):
		return item.hasType(_H_2)


	def onPrepare(self):
		_div__loc = _div
		unhealing = _div__loc(self.getP('unhealing'), 100.0)
		unhealing += _div__loc(self.getNumAffectedItems(_H_4) * self.getP('unhealing2'), 100.0)
		self.character().giveUnhealing(unhealing)

		self.connectToCharacterDebuffs("onDebuffsChanged")
		self.connectToOpponentBuffs("onOpponentBuffsChanged")


	def onDebuffsChanged(self, amount, event):
		if (amount > 0 and 
			isinstance(event.origin, _H_1) and 
			event.origin.character() == self.character()):

			regenToGive = 0
			for i in (amount if amount.__class__ is list else _iter(amount)):
				if self.rollChance():
					regenToGive += self.regen

			if regenToGive > 0:
				self.giveRegeneration(regenToGive, event)


	def onOpponentBuffsChanged(self, amount, event):
		if (amount < 0 and 
			isinstance(event.origin, _H_1) and 
			event.origin.character() == self.character()):

			for item in _iter(self.getAffectedItems()):
				item.addCritChancePercent(self.getChance2() * - amount)


	def doCooldownEffect(self):
		self.giveRandomBuffs(self.selfBuffs)
		self.giveRandomBuffs(self.opponentBuffs, None, _H_3.getBuffs(), self.opponent())
		self.activate()


	def playPickupSound(self):
		# decomp Items/Exclusive/EvilHat.gd:51 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/EvilHat.gd:55 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.selfBuffs = int(self.getP("buffs"))
		self.opponentBuffs = int(self.getP("buffs2"))
		self.regen = int(self.getP("regen"))


_R.reg("res://gd_core_items/Exclusive/EvilHat.gd", Exclusive__EvilHat)
_R.reg("EvilHat", Exclusive__EvilHat)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("Item")
try:
	_H_2 = _R.C("CoreConst").Type.Dark
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
_H_3 = _R.C("CoreConst")
try:
	_H_4 = _R.C('CoreConst').Affected.Secondary
except AttributeError as _he:
	_H_4 = _HoistPending(_he)
