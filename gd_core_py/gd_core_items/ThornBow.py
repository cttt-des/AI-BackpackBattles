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
if "_base_cls_ThornBow_2" not in globals():
	from .Bow import Bow_2 as _base_cls_ThornBow_2





class ThornBow_2(_base_cls_ThornBow_2):

	resource_path = "res://gd_core_items/ThornBow.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusCounter = 0
		self._tempBonusDam = 0

	@property
	def tempBonusDam(self):
		return self._tempBonusDam
	@tempBonusDam.setter
	def tempBonusDam(self, v):
		self._tempBonusDam = int(v)

	def hasAttackEffect(self):
		return True


	def onPrepare(self):
		self.bonusCounter = 0
		self.setState(self.bonusCounter)


	def onCombatStart(self):
		self.giveSpikes(self.getP1())
		self.activate(None, False)


	def doCooldownEffect(self):
		if self.useStamina() == _H_1:
			res = self.dealDamage()
			self.activate(res)

			if self.bonusCounter > 0:
				self.reduceBonusDamage(self.tempBonusDam * self.bonusCounter, False)
				self.bonusCounter = 0
				self.setState(self.bonusCounter, False, res.event)


	def onWeaponAttacked(self, damageRes):
		if damageRes.hasHit():
			attackEffectCount = 1 + self.rollDoubleAttackEffect()
			for i in (attackEffectCount if attackEffectCount.__class__ is list else _iter(attackEffectCount)):
				if self.character().getSpikes() > 0:
					self.bonusCounter += 1
					self.useSpikes(1, damageRes.event)
					self.addBonusDamage(self.tempBonusDam)
			self.setState(self.bonusCounter, False, damageRes.event)


	def onShopEntered(self):
		self.onStateChanged(0)


	def onStateChanged(self, _bonusCounter):
		if _bonusCounter > 0:
			pass
		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.tempBonusDam = self.getP2()


_R.reg("res://gd_core_items/ThornBow.gd", ThornBow_2)
_R.reg("ThornBow", ThornBow_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").StaminaResult.Sufficient
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
