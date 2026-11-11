# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

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
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_Stone_2" not in globals():
	from .Item import Item_2 as _base_cls_Stone_2





class Stone_2(_base_cls_Stone_2):

	resource_path = "res://gd_core_items/Stone.gd"

	def _init_fields(self):
		super()._init_fields()
		self._ammunition = 0
		self._bonusDamage = 0

	@property
	def ammunition(self):
		return self._ammunition
	@ammunition.setter
	def ammunition(self, v):
		self._ammunition = int(v)
	@property
	def bonusDamage(self):
		return self._bonusDamage
	@bonusDamage.setter
	def bonusDamage(self, v):
		self._bonusDamage = int(v)

	def combatEnd(self):
		super().combatEnd()
		self.ammunition = 1


	def setBagOfStones(self):
		self.ammunition = 9000


	def onPreDealDamage_late(self, damageRes):

		self.preHit()



	def preHit(self):
		self.removeBlock(self.getP1())


	def doCooldownEffect(self):
		if self.ammunition >= 1 and self.useStamina() == _H_2:
			self.ammunition -= 1

			res = self.dealDamage()

			if self.ammunition == 0:
				self.onAfterEffectFinished(False)
				self.consume(res)
			else:
				self.activate(res)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.onHit()



	def onHit(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _H_1().setItem(self)
		self.ammunition = 1



_R.reg("res://gd_core_items/Stone.gd", Stone_2)
_R.reg("Stone", Stone_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
_H_1 = _R.C("CoreDamageSource")
try:
	_H_2 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
