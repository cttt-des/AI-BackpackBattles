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
if "_base_cls_Exclusive__Toolbox" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__Toolbox





class Exclusive__Toolbox(_base_cls_Exclusive__Toolbox):

	resource_path = "res://gd_core_items/Exclusive/Toolbox.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speedReduction = None
		self.damBonusFactor = None


	def canLockBag(self):
		return True


	def canApplyEffect(self, toItem):
		return toItem.canBeEmpowered()


	def onPrepare(self):


		self.connectForCombat(self.opponent(), "character_attacked", "onOpponentDamaged")


	def onCombatStart(self):
		for item in _iter(self.getItemsInside()):
			if self.canApplyEffect(item):
				item.reduceSpeed(self.speedReduction)
				item.addBonusDamageFactor(self.damBonusFactor)


	def onOpponentDamaged(self, damageRes):
		if self.character().isBattleRaging():
			if damageRes.hasHit() and damageRes.damageSource.canApplyLifesteal():
				self.heal(ceil(_div(self.getP_m('lifesteal'), 100.0) * damageRes.damage), damageRes.event)








	def doCooldownEffect(self):
		self.character().startBattleRage(self, self.getP_m("dur_rage"))
		self.onAfterEffectFinished()

	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedReduction = _div__loc(self.getP('speedreduction'), 100.0)
		self.damBonusFactor = _div__loc(self.getP('dambonus'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Toolbox.gd", Exclusive__Toolbox)
_R.reg("Toolbox", Exclusive__Toolbox)
