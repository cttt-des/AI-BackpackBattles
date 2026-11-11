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
if "_base_cls_Exclusive__Recombobulator" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Recombobulator





class Exclusive__Recombobulator(_base_cls_Exclusive__Recombobulator):

	resource_path = "res://gd_core_items/Exclusive/Recombobulator.gd"

	def _init_fields(self):
		super()._init_fields()
		self.stable = True
		self.idleAnimation = None


	def canAffect(self, item):
		return not item.isBag() and (item.canStartNewRecipe() or item.bondedBaseItem == self)


	def cacheAffectedItemsForCombat(self):
		super().cacheAffectedItemsForCombat()
		arr = self.getItemsInAffectedCells_cached()
		self.cachedAffectedItems[_H_1] = arr




	def readyToFuse(self):
		if self.stable:
			return not (not self.bondedIngredients)
		else:
			return self.bondedBaseItem == None


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def reactToDropResult(self, dropResult):
		super().reactToDropResult(dropResult)
		if self.wasAddedToInventory(dropResult):
			pass


	def doCooldownEffect(self):
		self.giveRandomBuffs(1)
		self.cleanseRandomDebuffs(1)
		self.activate()


	def getCounterValue(self):
		return self.getAffectedGoldValue()

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/Recombobulator.gd", Exclusive__Recombobulator)
_R.reg("Recombobulator", Exclusive__Recombobulator)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Affected.Primary
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
