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
if "_base_cls_Exclusive__Ukulele" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Ukulele





class Exclusive__Ukulele(_base_cls_Exclusive__Ukulele):

	resource_path = "res://gd_core_items/Exclusive/Ukulele.gd"

	def _init_fields(self):
		super()._init_fields()
		self.nonMusicalItems = []
		self._activateIndex = 0
		self.options = []
		self.speedPerItem = None
		self.cdAdvance = None
		self.healAmp = None
		self.buffs = None
		self.cold = None

	@property
	def activateIndex(self):
		return self._activateIndex
	@activateIndex.setter
	def activateIndex(self, v):
		self._activateIndex = int(v)

	def canAffect(self, item):
		return True


	def canAffect_secondary(self, item):
		return item.hasType(_H_1)


	def onPrepare(self):
		_iter__loc = _iter
		self.activateIndex = 0
		self.nonMusicalItems.clear()
		for item in _iter__loc(self.inventory.getItems()):
			if ( not item.hasType(_H_1) and 
				item.hasCooldown()):
				self.nonMusicalItems.append(item)

		if not (not self.nonMusicalItems):
			self.ctx.rng.shuffleEngine(self.nonMusicalItems, 'Exclusive/Ukulele.gd:34')

			for item in _iter__loc(self.getAffectedItems(_H_2)):
				self.connectForCombat(item, "activated", "onItemActivated")

		self.addSpeed(self.speedPerItem * self.getNumAffectedItems())

		self.character().addHealingEfficiency(self.healAmp)

		for item in _iter__loc(self.inventory.getItems()):
			item.changeAmplificiationChancePercent_allBuffs(self.getChance())

		self.options = [0, 1, 2]


	def onItemActivated(self, event):


		while True:
			if (not self.nonMusicalItems):
				return

			item = self.nonMusicalItems[self.activateIndex]

			if item.isCooldownActive():


				item.advanceCooldownPercent(self.cdAdvance)
				self.activateIndex = _mod(self.activateIndex + 1, len(self.nonMusicalItems))
				break
			else:


				_erase(self.nonMusicalItems, item)
				if not (not self.nonMusicalItems):
					self.activateIndex %= len(self.nonMusicalItems)


	def doCooldownEffect(self):
		rng = self.ctx.util.pickRandomElement(self.options)
		if rng == 0:
			self.heal()
		elif rng == 1:
			self.giveRandomBuffs(self.buffs)
		else:
			self.inflictCold(self.cold)

		self.activate()

		self.options = [0, 1, 2]
		_erase(self.options, rng)


	def playPickupSound(self):
		# decomp Items/Exclusive/Ukulele.gd:90 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Ukulele.gd:94 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedPerItem = _div__loc(self.getP('speed'), 100.0)
		self.cdAdvance = self.getP("advance")
		self.healAmp = _div__loc(self.getP('healamp'), 100.0)
		self.buffs = int(self.getP("buffs"))
		self.cold = int(self.getP("cold"))


_R.reg("res://gd_core_items/Exclusive/Ukulele.gd", Exclusive__Ukulele)
_R.reg("Ukulele", Exclusive__Ukulele)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Musical
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Affected.Secondary
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
