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
if "_base_cls_Exclusive__SpellScrollIce" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__SpellScrollIce





class Exclusive__SpellScrollIce(_base_cls_Exclusive__SpellScrollIce):

	resource_path = "res://gd_core_items/Exclusive/SpellScrollIce.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self._coldInflicted = 0
		self.cold = None
		self.maxCold = None

	@property
	def coldInflicted(self):
		return self._coldInflicted
	@coldInflicted.setter
	def coldInflicted(self, v):
		self._coldInflicted = int(v)

	def canAffect(self, item):
		return item.hasType(_H_1) or (item.hasType(_H_2) and item.canActivate())


	def onPrepare(self):
		self.activated = False
		self.connectForCombat(self.character(), "pre_take_damage_late", "onCharacterAttacked")

		for item in _iter(self.getAffectedItems()):
			self.connectForCombat(item, "activated", "onShieldOrArmorActivated")
		self.coldInflicted = 0


	def onCharacterAttacked(self, damageRes):
		if not self.activated:
			if damageRes.willBeLethal(self.character()):
				opponentCold = self.opponent().getCold()
				if opponentCold > 0:
					self.activated = True
					self.opponent().loseCold(opponentCold, self, damageRes.event)
					self.giveBlock(gd_round(self.getBlock() * opponentCold), True, damageRes.event)
					self.consume()


	def onShieldOrArmorActivated(self, event):
		if self.coldInflicted < self.maxCold and self.rollChance():
			self.coldInflicted = min(self.cold, self.maxCold - self.coldInflicted)
			self.inflictCold(self.cold, event)
			self.miniActivate()

	def _readyInit(self):
		super()._readyInit()
		self.cold = self.getP("cold")
		self.maxCold = self.getP("max")


_R.reg("res://gd_core_items/Exclusive/SpellScrollIce.gd", Exclusive__SpellScrollIce)
_R.reg("SpellScrollIce", Exclusive__SpellScrollIce)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Type.Shield
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Armor
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
