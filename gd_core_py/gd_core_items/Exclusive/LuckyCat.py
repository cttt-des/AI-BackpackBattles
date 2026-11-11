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
if "_base_cls_Exclusive__LuckyCat" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__LuckyCat





class Exclusive__LuckyCat(_base_cls_Exclusive__LuckyCat):

	resource_path = "res://gd_core_items/Exclusive/LuckyCat.gd"

	def _init_fields(self):
		super()._init_fields()
		self.sales = None
		self.goldThreshold1 = None
		self.goldThreshold2 = None


	def canAffect(self, item):
		return True


	def getCounterValue(self):
		return self.getAffectedGoldValue()


	def condition1Fulfilled(self, gold):
		gold = int(gold)
		return gold > self.goldThreshold1


	def condition2Fulfilled(self, gold):
		return gold > self.goldThreshold2


	def onPrepare(self):
		gold = self.getCounterValue()
		if self.condition1Fulfilled(gold):


			self.character().changeCritResistance(self.getChance())

			if self.condition2Fulfilled(gold):
				bonusSpeed = _div(self.getP('speed'), 100.0)
				for item in _iter(self.inventory.getItems()):
					if self.canAffect_global(item):
						item.addSpeed(bonusSpeed)




	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		colors = [self.ctx.util.inactiveColor, self.ctx.util.inactiveColor]
		gold = None

		if self.placed:
			gold = self.getCounterValue()
			if self.condition1Fulfilled(gold):
				colors[0] = self.ctx.util.modifiedColor
				if self.condition2Fulfilled(gold):
					colors[1] = self.ctx.util.modifiedColor

		descr = self.getModeDescription(descr, colors, True, wrapInColor)






		return descr



	def updatePaws(self):
		gold = self.getCounterValue()
		if self.condition1Fulfilled(gold):
			if self.condition2Fulfilled(gold):
				pass
			else:
				pass
		else:
			pass

		self.updateShadowTexture()



	def onAffectedItemAdded(self, item, color):
		color = int(color)
		self.updatePaws()


	def onAffectedItemRemoved(self, item, color):
		color = int(color)
		self.updatePaws()


	def onAddToInventory(self):
		self.updatePaws()


	def onRemoveFromInventory(self):
		self.updateShadowTexture()


	def canAffect_global(self, item):
		return item.getRarity() >= _H_1 and item.hasCooldown()


	def onSaleRoll(self, _item):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.sales = _div(self.getP('sales'), 100.0)
		self.goldThreshold1 = self.getP("gold1")
		self.goldThreshold2 = self.getP("gold2")


_R.reg("res://gd_core_items/Exclusive/LuckyCat.gd", Exclusive__LuckyCat)
_R.reg("LuckyCat", Exclusive__LuckyCat)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Rarity.Godly
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
