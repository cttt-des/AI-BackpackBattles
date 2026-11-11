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
if "_base_cls_Exclusive__BustedBlade" not in globals():
	from ..Greatsword import Greatsword_2 as _base_cls_Exclusive__BustedBlade





class Exclusive__BustedBlade(_base_cls_Exclusive__BustedBlade):

	resource_path = "res://gd_core_items/Exclusive/BustedBlade.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusDamPerEmpower = None


	def onPrepare(self):
		self.setState(False)
		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")
		self.connectForCombat(self.character(), "character_empower_changed", "onEmpowerChanged")


	def onEmpowerChanged(self, amount, _event):
		self.changeVaryingDamage(amount * self.bonusDamPerEmpower)


	def onBattleRageStarted(self, _event):
		if not self.buffed:
			self.setState(True)
			self.baseCooldownOverride = self.getP3()
			self.updateBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)


	def onBattleRageEnded(self, _event):
		if self.buffed:
			self.setState(False)
			self.baseCooldownOverride = self.getBaseCooldown()
			self.updateBaseCooldown()
			self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)

	def _readyInit(self):
		super()._readyInit()
		self.bonusDamPerEmpower = self.getP1()


_R.reg("res://gd_core_items/Exclusive/BustedBlade.gd", Exclusive__BustedBlade)
_R.reg("BustedBlade", Exclusive__BustedBlade)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").ItemStat.StaminaCost
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
