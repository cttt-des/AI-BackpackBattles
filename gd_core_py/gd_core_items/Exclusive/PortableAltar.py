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
if "_base_cls_Exclusive__PortableAltar" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__PortableAltar





class Exclusive__PortableAltar(_base_cls_Exclusive__PortableAltar):

	resource_path = "res://gd_core_items/Exclusive/PortableAltar.gd"

	valueFactor = 1.0

	def canLockBag(self):
		return True


	def showBagBorderForItem(self, item):
		return not item.isBag()


	def onCombatStart(self):
		self.giveEmpower(self.getP("empower"))
		self.activate()




	def onRecipesUpdated(self):
		_iter__loc = _iter
		if self.ownerType != _H_1:
			return
		if self.fusing:
			return

		if self.locked or not self.placed:
			for bonded in (self.bondedIngredients if self.bondedIngredients.__class__ is list else _iter__loc(self.bondedIngredients)):
				bonded.removeBondedBaseItem()
			self.removeAllIngredients()
			return

		for item in _iter__loc(self.getItemsInside()):
			if item.canStartNewRecipe():
				self.createBondVisual(item)
				self.updateBondVisuals()
				item.addToBaseItem(self)


	def readyToFuse(self):
		return not (not self.bondedIngredients)


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def getCounterValue(self):
		gold = 0
		for item in (self.bondedIngredients if self.bondedIngredients.__class__ is list else _iter(self.bondedIngredients)):
			gold += item.getPrice()
		return gold

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/PortableAltar.gd", Exclusive__PortableAltar)
_R.reg("PortableAltar", Exclusive__PortableAltar)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Owner.PlayerInventory
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
