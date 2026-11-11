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
if "_base_cls_Exclusive__ExtraAngy" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ExtraAngy





class Exclusive__ExtraAngy(_base_cls_Exclusive__ExtraAngy):

	resource_path = "res://gd_core_items/Exclusive/ExtraAngy.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activated = False
		self.battleRageDur = 0.0


	def onPrepare(self):
		self.activated = False

		self.connectForCombat(self.character(), "battle_rage_started", "onBattleRageStarted")
		self.connectForCombat(self.character(), "battle_rage_ended", "onBattleRageEnded")


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def onBattleRageStarted(self, event):
		if not self.activated:
			self.battleRageDur = event.getParam("duration", 0)


	def onBattleRageEnded(self, _event):
		if not self.activated:
			self.activated = True

			self.activateCooldown()


	def doCooldownEffect(self):
		dur = _div(self.battleRageDur * self.getP_m('dur'), 100.0)
		self.character().startBattleRage(self, dur, None, False)
		self.onAfterEffectFinished()


	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Exclusive/ExtraAngy.gd", Exclusive__ExtraAngy)
_R.reg("ExtraAngy", Exclusive__ExtraAngy)
