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
if "_base_cls_Exclusive__EngineerBox" not in globals():
	from ..Bag import Bag_2 as _base_cls_Exclusive__EngineerBox





class Exclusive__EngineerBox(_base_cls_Exclusive__EngineerBox):

	resource_path = "res://gd_core_items/Exclusive/EngineerBox.gd"

	def _init_fields(self):
		super()._init_fields()
		self.queuedEmitters = []
		self.chargeTimer = None
		self.delay = None
		self.chargeSpeed = None


	def onCombatEnd(self):
		self.chargeTimer.stop()
		self.queuedEmitters.clear()


	def canApplyEffect(self, toItem):
		return toItem.has_method("emitCharge")


	def onPrepare(self):
		# ★ np24：录制镜像（gd_core/CoreContext.gd eb_relay_mirrored）——录制侧 EB
		#   ChargeTimer 首弹后队列不推进（探针实证 fire=1 次/侧、ts=0），接力重发射
		#   =0；gd 侧 CoreTimer 级联=接力活跃（sendCharge +10）。镜像=连接环不建。
		# ★ np25棋盘面重建回植：builder 从 decompiled 再生无此手补（chessfix 重建
		#   实测被冲掉），漏植则 EB 接力语义回退。
		if self.ctx != None and self.ctx.eb_relay_mirrored:
			return
		for item in _iter(self.getAffectedItemsInside()):
			self.ctx.bus.connectEvent(item, "charge_emitted", self, "onItemInsideEmittedCharge")


	def onItemInsideEmittedCharge(self, item):
		self.queuedEmitters.append(item)
		self.chargeTimer.start(self.delay)


	def onChargeTimerTimeout(self):
		emitter = self.queuedEmitters.pop(0)
		emitter.emitCharge(self.chargeSpeed)

	def _readyInit(self):
		super()._readyInit()
		self.chargeTimer = self.newItemTimer("ChargeTimer", "onChargeTimerTimeout", True)
		self.delay = self.getP("delay")
		self.chargeSpeed = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/EngineerBox.gd", Exclusive__EngineerBox)
_R.reg("EngineerBox", Exclusive__EngineerBox)
