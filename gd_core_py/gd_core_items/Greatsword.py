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
if "_base_cls_Greatsword_2" not in globals():
	from .Weapon import Weapon_2 as _base_cls_Greatsword_2





class Greatsword_2(_base_cls_Greatsword_2):

	resource_path = "res://gd_core_items/Greatsword.gd"

	def _init_fields(self):
		super()._init_fields()
		self.buffed = False
		self.buffParticles = None
		self.empowerNeeded = None
		self.buffedStamina = None
		self.buffedCooldown = None


	def isBuffed(self):
		return self.buffed



	def getStaminaCost(self):
		override = self.statDisplayOverrides[_H_1]
		if override:
			return override

		if self.isBuffed():
			return self.buffedStamina * self.staminaFactor
		else:
			return super().getStaminaCost()


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "character_empower_changed", "empowerChanged")


	def empowerChanged(self, amount, event):
		if not self.buffed and self.character().getEmpower() >= self.empowerNeeded:
			self.setState(True)
			self.setBaseCooldown(self.buffedCooldown)
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)

		elif self.buffed and self.character().getEmpower() < self.empowerNeeded:
			self.setState(False)
			self.resetBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, _buffed):
		self.buffed = _buffed
		if self.buffed:
			pass
		else:
			pass


	def _readyInit(self):
		super()._readyInit()
		self.empowerNeeded = int(self.getP1())
		self.buffedStamina = self.getP2()
		self.buffedCooldown = self.getP3()


_R.reg("res://gd_core_items/Greatsword.gd", Greatsword_2)
_R.reg("Greatsword", Greatsword_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").ItemStat.StaminaCost
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
